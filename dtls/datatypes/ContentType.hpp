#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#section-6.2.1

namespace dtls
{
    enum class ContentType : std::uint8_t
    {
        change_cipher_spec = 20,
        alert = 21,
        handshake = 22,
        application_data = 23
        //(255)
    };
}