#pragma once

#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.1

namespace dtls
{
    struct GenericAEADCipher
    {
        std::byte *nonce_explicit; // SecurityParameters.record_iv_length

        // aead-ciphered
        std::byte *content; // TLSCompressed.length
    };
}