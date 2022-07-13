#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace dtls
{
    enum class HashAlgorithm : std::uint8_t
    {
        none = 0,
        md5 = 1,
        sha1 = 2,
        sha224 = 3,
        sha256 = 4,
        sha384 = 5,
        sha512 = 6
        //(255)
    };
}