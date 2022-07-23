#pragma once

#include <cstddef>
#include <cstdint>
#include "Array.hpp"

namespace crispy
{
	struct AddrInfo
	{
		Array<std::byte> address;
		std::uint16_t port;

		bool isV6()
		{
			return address.size == 16;
		}

		bool isV4()
		{
			return address.size == 4;
		}

		friend bool operator==(const AddrInfo& lhs, const AddrInfo& rhs)
		{
			return lhs.address == rhs.address && lhs.port == rhs.port;
		}
	};
}