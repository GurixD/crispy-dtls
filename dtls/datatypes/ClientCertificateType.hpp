#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.2

namespace crispy
{
    enum class ClientCertificateType : std::uint8_t
    {
        rsa_sign = 1,
        dss_sign = 2,
        rsa_fixed_dh = 3,
        dss_fixed_dh = 4,
        rsa_ephemeral_dh_RESERVED = 5,
        dss_ephemeral_dh_RESERVED = 6,
        fortezza_dms_RESERVED = 20,
        ecdsa_sign = 64,
        rsa_fixed_ecdh = 65,
        ecdsa_fixed_ecdh = 66,
        gost_sign256 = 67,
        gost_sign512 = 68
        //(255)
    };
}