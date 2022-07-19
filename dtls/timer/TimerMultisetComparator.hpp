#pragma once

#include "Types.hpp"

namespace crispy
{
	namespace timer
	{
		class TimerMultisetComparator
		{
		public:
			bool operator()(const Item& lhs, const Item& rhs) const;
		};
	}
}