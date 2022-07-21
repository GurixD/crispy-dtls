#pragma once

#include <set>
#include <vector>
#include <tuple>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <cstdint>

#include "TimerMultisetComparator.hpp"
#include "Types.hpp"
#include "TimerDestructor.hpp"

namespace crispy
{
	namespace timer
	{
		class Timer
		{
		private:
			std::uint32_t id;

			explicit Timer(std::uint32_t id);

			std::uint32_t getId();


			// TODO: add all static variable in other class (friending this) and add class as static here instead
			static std::thread threadLoop;
			static std::condition_variable cond;
			static std::mutex multisetMutex;
			static std::multiset<Item, TimerMultisetComparator> timerFunctions;
			static bool running;
			static TimerDestructor timerDestructor;

			static void loop();
			static TimePoint now();
			static void destructor();
			static std::uint32_t firstFreeId();
			static std::multiset<Item>::iterator findId(std::uint32_t id);
			static std::multiset<Item>::iterator findTimer(Timer timer);

			friend class TimerDestructor;
		public:
			void stop();
			bool isRunning();

			static Timer setTimeout(Action action, Duration duration);
			static Timer setNTimeout(Action action, Duration duration, std::int64_t n);
			static Timer setInterval(Action action, Duration duration);
		};
	}
}
