#pragma once

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.6

namespace crispy
{
    enum class MACAlgorithm
    {
        null,
        hmac_md5,
        hmac_sha1,
        hmac_sha256,
        hmac_sha384,
        hmac_sha512
    };
}