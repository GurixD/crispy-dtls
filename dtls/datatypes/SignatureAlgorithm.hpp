#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace dtls
{
    enum class SignatureAlgorithm : std::uint8_t
    {
        anonymous = 0,
        rsa = 1,
        dsa = 2,
        ecdsa = 3
        //(255)
    };
}