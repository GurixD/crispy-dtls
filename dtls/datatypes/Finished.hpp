#pragma once

#include <cstddef>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.4

namespace dtls
{
    struct Finished
    {
        std::byte *verify_data; // [verify_data_length] => default and at least = 12 (https://datatracker.ietf.org/doc/html/rfc5246#section-7.4.9)
    };
}