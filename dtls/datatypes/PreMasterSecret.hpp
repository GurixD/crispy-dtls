#pragma once

#include "ProtocolVersion.hpp"
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.3

namespace crispy
{
    struct PreMasterSecret
    {
        ProtocolVersion client_version;
        std::byte random[46];
    };
}
