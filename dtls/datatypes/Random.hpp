#pragma once

#include "../bigendian/integer.hpp"
#include <cstddef>
#include <string>
#include "../DataReader.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace crispy
{
    struct Random
    {
        bigendian::uint32 gmt_unix_time;
        std::byte random_bytes[28];

        std::string toString() const;

        static Random fromData(DataReader& dr);
    };
}