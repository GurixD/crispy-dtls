#pragma once

#include "ProtocolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"
#include <cstdint>
#include <cstddef>
#include <vector>
#include "../bigendian/integer.hpp"
#include "CipherSuite.hpp"
#include "CompressionMethod.hpp"
#include "Extension.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.2 (dtls)
// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1 (tls for extensions)

namespace crispy
{

    struct ClientHello
    {
        ProtocolVersion client_version;
        Random random;
        SessionID session_id;
        std::uint8_t cookie_length;                         // <0..2 ^ 8 - 1>
        std::vector<std::byte> cookie; 
        bigendian::uint16 cipher_suites_length;             // <2..2 ^ 16 - 1>
        std::vector<CipherSuite> cipher_suites;
        std::uint8_t compression_methods_length;            // <1..2 ^ 8 - 1>
        std::vector<CompressionMethod> compression_methods;
        bigendian::uint16 extensions_length;                // <0..2 ^ 16 - 1>
        std::vector<Extension> extensions;

        static std::tuple<ClientHello, bool> fromData(DataReader& dr);
        

        std::string toString();
    };

}