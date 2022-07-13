#pragma once

#include "../bigendian/uintnbits.hpp"
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace dtls
{
	struct ASN1Cert
	{
		bigendian::uint24 ASN1_cert_length; // <2 ^ 24 - 1> wtf ???
		std::byte *ASN1_cert;
	};
}