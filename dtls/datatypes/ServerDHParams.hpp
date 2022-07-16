#pragma once

#include "../bigendian/integer.hpp"
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace crispy
{
    /* Ephemeral DH parameters */
    struct ServerDHParams
    {
        bigendian::uint16 dh_p_length; // <1..2 ^ 16 - 1>
        std::byte *dh_p;
        bigendian::uint16 dh_g_length; // <1..2 ^ 16 - 1>
        std::byte *dh_g;
        bigendian::uint16 dh_Ys_length; // <1..2 ^ 16 - 1>
        std::byte *dh_Ys;
    };
}