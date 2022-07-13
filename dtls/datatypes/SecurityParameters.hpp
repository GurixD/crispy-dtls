#pragma once

#include "ConnectionEnd.hpp"
#include "PRFAlgorithm.hpp"
#include "BulkCipherAlgorithm.hpp"
#include "CipherType.hpp"
#include <cstdint>
#include "MACAlgorithm.hpp"
#include "CompressionMethod.hpp"
#include <cstddef>
#include <cstring>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.6

namespace dtls
{
    struct SecurityParameters
    {
        ConnectionEnd entity;
        PRFAlgorithm prf_algorithm;
        BulkCipherAlgorithm bulk_cipher_algorithm;
        CipherType cipher_type;
        std::uint8_t enc_key_length;
        std::uint8_t block_length;
        std::uint8_t fixed_iv_length;
        std::uint8_t record_iv_length;
        MACAlgorithm mac_algorithm;
        std::uint8_t mac_length;
        std::uint8_t mac_key_length;
        CompressionMethod compression_algorithm;
        std::byte master_secret[48];
        std::byte client_random[32];
        std::byte server_random[32];

        SecurityParameters(ConnectionEnd ce, CipherType ct) : 
            entity(ce),
            prf_algorithm(PRFAlgorithm::tls_prf_sha256),
            bulk_cipher_algorithm(BulkCipherAlgorithm::null),
            cipher_type(ct),
            mac_algorithm(MACAlgorithm::null),
            block_length(0),
            compression_algorithm(CompressionMethod::null),
            enc_key_length(0),
            fixed_iv_length(0),
            mac_key_length(0),
            mac_length(0),
            record_iv_length(0)
        {
            std::memset(this->master_secret, 0, sizeof(master_secret));
            std::memset(this->client_random, 0, sizeof(client_random));
            std::memset(this->server_random, 0, sizeof(server_random));
        }
    };
}