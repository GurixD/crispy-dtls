#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.2

namespace dtls
{
    enum class ChangeCipherSpecEnum : std::uint8_t
    {
        change_cipher_spec = 1
        // (255)
    };

    struct ChangeCipherSpec
    {
        ChangeCipherSpecEnum type;
    };
}