#pragma once

#include "ProtocolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"
#include "CipherSuite.hpp"
#include "CompressionMethod.hpp"
#include "../bigendian/integer.hpp"
#include "Extension.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace crispy
{
    struct ServerHello
    {
        ProtocolVersion server_version;
        Random random;
        SessionID session_id;
        CipherSuite cipher_suite;
        CompressionMethod compression_method;
    };

    struct ServerHelloWithExtensions : public ServerHello
    {
        bigendian::uint16 extensions_length; // <0..2 ^ 16 - 1>
        Extension *extensions;
    };
}