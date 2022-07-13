#pragma once

#include "ContentType.hpp"
#include "ProtocolVersion.hpp"
#include "../bigendian/uintnbits.hpp"
#include "../bigendian/integer.hpp"
#include <cstddef>
#include <vector>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.1

namespace dtls
{
    struct DTLSCiphertext
    {
        ContentType type;
        ProtocolVersion version;
        bigendian::uint16 epoch;
        bigendian::uint48 sequence_number;
        bigendian::uint16 length;

        // select(CipherSpec.cipher_type) {
        //       case block:  GenericBlockCipher;
        //       case aead:   GenericAEADCipher;
        // } fragment;
        std::vector<std::byte> fragment;
    };
}