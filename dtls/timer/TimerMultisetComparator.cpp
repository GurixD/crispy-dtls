#include "TimerMultisetComparator.hpp"

#include <functional>

namespace crispy
{
	namespace timer
	{
		bool TimerMultisetComparator::operator()(const Item& lhs, const Item& rhs) const
		{
			return std::less{}(std::get<0>(lhs), std::get<0>(rhs));
		}
	}
}