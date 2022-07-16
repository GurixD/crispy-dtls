#pragma once

#include "../bigendian/integer.hpp"
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace crispy
{
	struct DistinguishedName
	{
		bigendian::uint16 distinguished_name_length; // <1..2^16-1>
		std::byte *distinguished_name;
	};
}