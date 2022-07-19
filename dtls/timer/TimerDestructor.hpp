#pragma once

namespace crispy
{
	namespace timer
	{
		class TimerDestructor
		{
		private:
			TimerDestructor();

			friend class Timer;
		public:
			~TimerDestructor();
		};
	}
}
