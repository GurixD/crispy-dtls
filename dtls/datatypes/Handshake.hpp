#pragma once

#include "HandshakeType.hpp"
#include "../bigendian/uintnbits.hpp"
#include "../bigendian/integer.hpp"
#include <vector>
#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.2

namespace crispy
{
    struct Handshake
    {
        HandshakeType msg_type;
        bigendian::uint24 length;
        bigendian::uint16 message_seq;
        bigendian::uint24 fragment_offset;
        bigendian::uint24 fragment_length;

        // select(HandshakeType) {
        //    case hello_request: HelloRequest;
        //    case client_hello:  ClientHello;
        //    case server_hello:  ServerHello;
        //    case hello_verify_request: HelloVerifyRequest;
        //    case certificate:Certificate;
        //    case server_key_exchange: ServerKeyExchange;
        //    case certificate_request: CertificateRequest;
        //    case server_hello_done:ServerHelloDone;
        //    case certificate_verify:  CertificateVerify;
        //    case client_key_exchange: ClientKeyExchange;
        //    case finished: Finished;
        // } body;

        std::vector<std::byte> body;
    };
}