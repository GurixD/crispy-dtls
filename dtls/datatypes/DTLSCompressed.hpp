#pragma once

#include "ContentType.hpp"
#include "ProtocolVersion.hpp"
#include "../bigendian/integer.hpp"
#include "../bigendian/uintnbits.hpp"
#include <cstdint>
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.1

namespace dtls
{
	struct DTLSCompressed
	{
		ContentType type;
		ProtocolVersion version;
		bigendian::uint16 epoch;
		bigendian::uint48 sequence_number;
		bigendian::uint16 length;
		std::byte *fragment;
	};
}