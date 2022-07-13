#pragma once

#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.3

namespace dtls
{
    struct CertificateVerify
    {
        // digitally-signed struct
        std::byte *handshake_messages; // [handshake_messages_length]
    };
}