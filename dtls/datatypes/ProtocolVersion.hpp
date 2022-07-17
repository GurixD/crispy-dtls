#pragma once

#include <cstdint>
#include <string>

// https://datatracker.ietf.org/doc/html/rfc5246#section-6.2.1

namespace crispy
{
    struct ProtocolVersion
    {
        std::uint8_t major;
        std::uint8_t minor;

        std::string toString() const;

        static const ProtocolVersion DTLS1_0;
        static const ProtocolVersion DTLS1_2;
        static const ProtocolVersion DTLS1_3;

        static const ProtocolVersion SupportedProtocolVersions[];

        static constexpr bool isSupported(ProtocolVersion protocolVersion);

        friend bool operator==(const ProtocolVersion &lhs, const ProtocolVersion &rhs);
    };
}