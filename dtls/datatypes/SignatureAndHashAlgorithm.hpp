#pragma once

#include "HashAlgorithm.hpp"
#include "SignatureAlgorithm.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace crispy
{
    struct SignatureAndHashAlgorithm
    {
        HashAlgorithm hash;
        SignatureAlgorithm signature;
    };
}