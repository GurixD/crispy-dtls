#pragma once

#include "ServerDHParams.hpp"
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace crispy
{
    struct ServerKeyExchange
    {
    };

    struct ServerKeyExchangeDHParams : public ServerKeyExchange
    {
        ServerDHParams params;
    };

    struct SignedParams
    {
        std::byte client_random[32];
        std::byte server_random[32];
        ServerDHParams params;
    };

    struct ServerKeyExchangeDHParamsSign : public ServerKeyExchangeDHParams
    {
        // digitally-signed struct
        SignedParams signed_params;
    };
}