#pragma once

#include "PreMasterSecret.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.3

namespace dtls
{
    struct EncryptedPreMasterSecret
    {
        // public-key-encrypted
        PreMasterSecret pre_master_secret;
    };
}