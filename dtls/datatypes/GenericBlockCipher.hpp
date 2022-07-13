#pragma once

#include <cstddef>
#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.1

namespace dtls
{
    struct GenericBlockCipher
    {
        std::byte *IV; // SecurityParameters.record_iv_length

        // block-ciphered
        std::byte *content;    // TLSCompressed.length
        std::byte *MAC;        // SecurityParameters.mac_length
        std::uint8_t *padding; // GenericBlockCipher.padding_length
        std::uint8_t padding_length;
    };
}