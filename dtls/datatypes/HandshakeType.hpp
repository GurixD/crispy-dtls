#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.2

namespace dtls
{
    enum class HandshakeType : std::uint8_t
    {
        hello_request = 0,
        client_hello = 1,
        server_hello = 2,
        hello_verify_request = 3,
        certificate = 11,
        server_key_exchange = 12,
        certificate_request = 13,
        server_hello_done = 14,
        certificate_verify = 15,
        client_key_exchange = 16,
        finished = 20
        //(255)
    };
}