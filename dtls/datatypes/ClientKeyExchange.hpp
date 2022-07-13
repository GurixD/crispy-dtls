#pragma once

#include "EncryptedPreMasterSecret.hpp"
#include "ClientDiffieHellmanPublic.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.3

// select(KeyExchangeAlgorithm) {
//     case rsa:
//         EncryptedPreMasterSecret;
//     case dhe_dss:
//     case dhe_rsa:
//     case dh_dss:
//     case dh_rsa:
//     case dh_anon:
//         ClientDiffieHellmanPublic;
// } exchange_keys;

namespace dtls
{
    // rsa
    struct ClientKeyExchangeEncryptedPreMasterSecret
    {
        EncryptedPreMasterSecret exchange_keys;
    };

    // all the others
    struct ClientKeyExchangeClientDiffieHellmanPublic
    {
        ClientDiffieHellmanPublicExplicit exchange_keys;
    };
}