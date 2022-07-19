#pragma once

#include <set>
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
			static std::thread threadLoop;
			static std::condition_variable cond;
			static std::mutex condMutex;
			static std::mutex listMutex;
			static std::multiset<Item, TimerMultisetComparator> timerFunctions;
			static bool running;
			static TimerDestructor timerDestructor;

			Timer();

			static void loop();
			static TimePoint now();
			static void destructor();

			friend class TimerDestructor;
		public:
			static void setTimeout(Action action, Duration duration);
			static void setNTimeout(Action action, Duration duration, std::int64_t n);
			static void setInterval(Action action, Duration duration);
		};
	}
}
