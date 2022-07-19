#include "Timer.hpp"


namespace crispy
{
	namespace timer
	{
		// Using lambda to set order of initialization
		std::condition_variable Timer::cond = [] {return std::condition_variable(); }();
		std::mutex Timer::listMutex = [] {return std::mutex(); }();
		std::mutex Timer::condMutex = [] {return std::mutex(); }();
		std::multiset<Item, TimerMultisetComparator> Timer::timerFunctions = [] {return std::multiset<Item, TimerMultisetComparator>(); }();
		bool Timer::running = [] {return true; }();
		std::thread Timer::threadLoop = [] {return std::thread(loop); }();

		// Destructor order is in reverse order of constructor so this needs to be constructed in last
		TimerDestructor Timer::timerDestructor = [] {return TimerDestructor{}; }();

		Timer::Timer()
		{

		}


		void Timer::loop()
		{
			while (running)
			{
				std::unique_lock<std::mutex> conditionLock(condMutex);
				if (timerFunctions.empty())
				{
					cond.wait(conditionLock);
				}
				else
				{
					auto [timer, func, duration, n] = *timerFunctions.begin();
					auto status = cond.wait_until(conditionLock, timer);
					if (status == std::cv_status::timeout)
					{
						// run method (call on other thread?)
						func();

						{
							std::scoped_lock lock(listMutex);
							timerFunctions.erase(timerFunctions.begin());

							switch (n)
							{
							case -1:
								timerFunctions.insert(std::make_tuple(now() + duration, func, duration, -1));
								break;
							case 0:
							case 1:
								break;
							default:
								timerFunctions.insert(std::make_tuple(now() + duration, func, duration, n - 1));
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

		void addTimer()
		{
		}

		void Timer::destructor()
		{
			running = false;
			cond.notify_one();
			threadLoop.join();
		}


		void Timer::setNTimeout(Action action, Duration duration, std::int64_t n)
		{
			// Prevent negative values (except -1)
			if (n <= 0 && n != -1)
				return;

			TimePoint timePoint = now() + duration;

			std::scoped_lock lock(listMutex);

			auto it = timerFunctions.insert(std::make_tuple(timePoint, action, duration, n));
			if (it == timerFunctions.begin())
			{
				cond.notify_one();
			}
		}

		void Timer::setTimeout(Action action, Duration duration)
		{
			setNTimeout(action, duration, 1);
		}

		void Timer::setInterval(Action action, Duration duration)
		{
			setNTimeout(action, duration, -1);
		}
	}
}
