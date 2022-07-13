#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.6

namespace dtls
{
	enum class CompressionMethod : std::uint8_t
	{
		null = 0
		//(255)
	};
}