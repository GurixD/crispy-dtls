#include "ClientHello.hpp"

#include <sstream>

namespace crispy
{
	std::string Random::toString() const
    {
        std::ostringstream ss;
        ss << "Random: " << std::endl
            << "\tTime: " << this->gmt_unix_time.get() << std::endl;
        ss << "\tRandom: " << Helper::byteArrayToString(this->random_bytes, sizeof(this->random_bytes)) << std::endl;
        return ss.str();
    }

    Random Random::fromData(DataReader& dr)
    {
        Random random{};

        random.gmt_unix_time = dr.read<bigendian::uint32>();
        dr.read(random.random_bytes, sizeof(random.random_bytes));

        return random;
    }
}