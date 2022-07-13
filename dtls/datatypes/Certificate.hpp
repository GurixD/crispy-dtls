#pragma once

#include "../bigendian/uintnbits.hpp"
#include "ASN1Cert.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace dtls
{
    struct Certificate
    {
        bigendian::uint24 certificate_list_length; // <0..2 ^ 24 - 1>
        ASN1Cert certificate_list;
    };
}