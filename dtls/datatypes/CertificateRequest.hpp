#pragma once

#include <cstdint>
#include "ClientCertificateType.hpp"
#include "../bigendian/integer.hpp"
#include "DistinguishedName.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace dtls
{
    struct CertificateRequest
    {
        std::uint8_t certificate_types_length; // <1..2 ^ 8 - 1>
        ClientCertificateType *certificate_types;
        bigendian::uint16 certificate_authorities_length; // <0..2 ^ 16 - 1>
        DistinguishedName *certificate_authorities;
    };
}