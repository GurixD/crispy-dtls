#pragma once

#include "../bigendian/integer.hpp"
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.3

// select(PublicValueEncoding) {
//     case implicit: struct {};
//     case explicit: opaque DH_Yc<1..2 ^ 16 - 1>;
// } dh_public;

namespace crispy
{
	struct ClientDiffieHellmanPublicImplicit
	{
	};

	struct ClientDiffieHellmanPublicExplicit
	{
		bigendian::uint16 DH_Yc_length; // <1..2 ^ 16 - 1>
		std::byte *DH_Yc;
	};
}