#pragma once

#include "ProtocolVersion.hpp"
#include <cstdint>
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.2

namespace crispy
{
    struct HelloVerifyRequest
    {
        ProtocolVersion server_version;
        std::uint8_t cookie_length; //<0..2 ^ 8 - 1>
        std::byte *cookie;
    };
}