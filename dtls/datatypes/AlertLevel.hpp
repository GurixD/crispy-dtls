#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.3

namespace crispy
{
	enum class AlertLevel : std::uint8_t
	{
		warning = 1,
		fatal = 2
		//(255)
	};
}