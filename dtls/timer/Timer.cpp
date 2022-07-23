#include "Timer.hpp"

#include <iostream>

namespace crispy
{
	namespace timer
	{
		// Using lambda to set order of initialization
		std::condition_variable Timer::cond = [] {return std::condition_variable(); }();
		std::mutex Timer::multisetMutex = [] {return std::mutex(); }();
		std::multiset<Item, TimerMultisetComparator> Timer::timerFunctions = [] {return std::multiset<Item, TimerMultisetComparator>(); }();
		bool Timer::running = [] {return true; }();
		std::thread Timer::threadLoop = [] {return std::thread(loop); }();

		// Destructor order is in reverse order of constructor so this needs to be constructed in last
		TimerDestructor Timer::timerDestructor = [] {return TimerDestructor{}; }();

		Timer::Timer(Action action, Duration duration, std::int64_t n) : id(0), action(action), duration(duration), n(n)
		{

		}

		std::uint32_t Timer::getId()
		{
			return this->id;
		}

		// Cancel timer
		void Timer::stop()
		{
			std::scoped_lock lock(multisetMutex);

			auto it = findTimer(*this);
			if (it != timerFunctions.end())
			{
				bool first = it == timerFunctions.begin();
				timerFunctions.erase(it);
				if (first)
				{
					cond.notify_one();
				}
			}

			this->id = 0;
		}

		void Timer::start()
		{
			if (!isRunning())
			{
				TimePoint timePoint = now() + duration;

				std::scoped_lock lock(multisetMutex);

				auto id = firstFreeId();

				auto it = timerFunctions.insert(std::make_tuple(timePoint, action, duration, n, id));
				if (it == timerFunctions.begin())
				{
					cond.notify_one();
				}
			}
		}

		bool Timer::isRunning()
		{
			if (this->id == 0)
				return false;

			std::scoped_lock lock(multisetMutex);

			auto it = findTimer(*this);
			return it != timerFunctions.end();
		}

		void Timer::loop()
		{
			while (running)
			{
				std::unique_lock<std::mutex> conditionLock(multisetMutex);
				if (timerFunctions.empty())
				{
					cond.wait(conditionLock);
					conditionLock.unlock();
				}
				else
				{
					auto [timer, func, duration, n, id] = *timerFunctions.begin();
					auto status = cond.wait_until(conditionLock, timer);
					conditionLock.unlock();

					// Only call function if it was a timeout
					if (status == std::cv_status::timeout)
					{
						// run method (call on other thread?)
						func();

						{
							std::scoped_lock lock(multisetMutex);
							auto it = findId(id);
							if (it != timerFunctions.end())
								timerFunctions.erase(it);

							switch (n)
							{
							case -1:
								timerFunctions.insert(std::make_tuple(timer + duration, func, duration, -1, id));
								break;
							case 0:
							case 1:
								break;
							default:
								timerFunctions.insert(std::make_tuple(timer + duration, func, duration, n - 1, id));
								break;
							}
						}
					}
				}
			}
		}

		TimePoint Timer::now()
		{
			return std::chrono::steady_clock::now();
		}


		void Timer::destructor()
		{
			running = false;
			cond.notify_one();
			threadLoop.join();
		}

		std::uint32_t Timer::firstFreeId()
		{
			std::vector<std::uint32_t> ids(timerFunctions.size());
			for (const auto& item : timerFunctions)
			{
				ids.push_back(std::get<4>(item));
			}

			// keep id 0 for invalid timers
			for (std::uint32_t id = 1; 0 < std::numeric_limits<std::uint32_t>::max(); ++id)
			{
				auto it = std::find(ids.begin(), ids.end(), id);
				if (it == ids.end())
					return id;
			}

			throw std::runtime_error("No id available");
		}

		std::multiset<Item>::iterator Timer::findId(std::uint32_t id)
		{
			return std::find_if(timerFunctions.begin(), timerFunctions.end(), [id](const Item& item) { return std::get<4>(item) == id; });
		}

		std::multiset<Item>::iterator Timer::findTimer(Timer timer)
		{
			return findId(timer.getId());
		}

		Timer Timer::setNTimeout(Action action, Duration duration, std::int64_t n, bool startImmediatly)
		{
			// Prevent negative values (except -1)
			if (n <= 0 && n != -1)
				return Timer{};

			Timer timer(action, duration, n);

			if (startImmediatly)
				timer.start();


			return timer;
		}

		Timer Timer::setTimeout(Action action, Duration duration, bool startImmediatly)
		{
			return setNTimeout(action, duration, 1, startImmediatly);
		}

		Timer Timer::setInterval(Action action, Duration duration, bool startImmediatly)
		{
			return setNTimeout(action, duration, -1, startImmediatly);
		}
	}
}
