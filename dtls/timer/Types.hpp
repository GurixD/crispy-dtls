#pragma once

#include <chrono>
#include <tuple>
#include <functional>

namespace crispy
{
	namespace timer
	{
		using TimePoint = std::chrono::steady_clock::time_point;
		using Duration = std::chrono::steady_clock::duration;
		using Action = std::function<void(void)>;
		using Item = std::tuple<TimePoint, Action, Duration, std::int64_t, std::uint32_t>;
	}
}