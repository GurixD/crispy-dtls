#pragma once

#include "ContentType.hpp"
#include "ProtocolVersion.hpp"
#include <cstdint>
#include "../bigendian/uintnbits.hpp"
#include "../bigendian/integer.hpp"
#include <vector>
#include <cstddef>
#include "../DataReader.hpp"
#include <cstring>
#include <sstream>
#include <iomanip>

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.1

namespace crispy
{
    struct DTLSPlaintext
    {
        ContentType type;
        ProtocolVersion version;
        bigendian::uint16 epoch;
        bigendian::uint48 sequence_number;
        bigendian::uint16 length;
        std::vector<std::byte> fragment;

        static std::tuple<DTLSPlaintext, bool> fromData(DataReader &dr)
        {
            DTLSPlaintext plainText{};
            dr.startTransaction();

            plainText.type = static_cast<ContentType>(dr.read<std::uint8_t>());
            plainText.version.major = dr.read<std::uint8_t>();
            plainText.version.minor = dr.read<std::uint8_t>();
            plainText.epoch = dr.read<bigendian::uint16>();
            plainText.sequence_number = dr.read<bigendian::uint48>();
            plainText.length = dr.read<bigendian::uint16>();
            plainText.fragment = std::vector<std::byte>(plainText.length.get());
            dr.read(plainText.fragment);

            bool ok = dr.checkTransaction();
            return {plainText, ok};
        }

        std::string toString() const
        {
            std::ostringstream ss;
            ss << "DTLSPlaintext: " << std::endl;
            ss << "ContentType: " << static_cast<std::uint16_t>(this->type) << std::endl;
            ss << "ProtocolVersion: " << static_cast<std::uint16_t>(this->version.major) << "." << static_cast<std::uint16_t>(this->version.minor) << std::endl;
            ss << "Epoch: " << this->epoch.get() << std::endl;
            ss << "Sequence number: " << this->sequence_number.get<std::uint64_t>() << std::endl;
            ss << "Length: " << this->length.get() << std::endl;

            ss << std::hex;
            for (auto b : this->fragment)
            {
                ss << std::setfill('0') << std::setw(2) << static_cast<std::uint16_t>(b) << " ";
            }
            ss << std::dec;

            return ss.str();
        }
    };
}