#pragma once

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace crispy
{
    enum class KeyExchangeAlgorithm
    {
        dhe_dss,
        dhe_rsa,
        dh_anon,
        rsa,
        dh_dss,
        dh_rsa
        /* may be extended, e.g., for ECDH -- see [TLSECC] */
    };
}