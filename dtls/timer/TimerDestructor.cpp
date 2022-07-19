#include "TimerDestructor.hpp"

#include "Timer.hpp"

namespace crispy
{
	namespace timer
	{
		TimerDestructor::TimerDestructor() {}

		TimerDestructor::~TimerDestructor()
		{
			Timer::destructor();
		}
	}
}