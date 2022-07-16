#pragma once

#include "../bigendian/integer.hpp"
#include <cstddef>
#include <string>
#include <iomanip>
#include <sstream>
#include "../DataReader.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace crispy
{
    struct Random
    {
        bigendian::uint32 gmt_unix_time;
        std::byte random_bytes[28];

        std::string toString()
        {
            std::ostringstream ss;
            ss << "Random: " << std::endl
               << "\tTime: " << this->gmt_unix_time.get() << std::endl;
            ss << "\tRandom: " << Helper::byteArrayToString(this->random_bytes, sizeof(this->random_bytes));
            return ss.str();
        }

        static Random fromData(DataReader &dr)
        {
            Random random{};

            random.gmt_unix_time = dr.read<bigendian::uint32>();
            dr.read(random.random_bytes, sizeof(random.random_bytes));

            return random;
        }
    };
}