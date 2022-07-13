#pragma once

#include <cstdint>

// https://datatracker.ietf.org/doc/html/rfc5246#section-6.2.1

namespace dtls
{
    struct ProtocolVersion
    {
        std::uint8_t major;
        std::uint8_t minor;

        static const ProtocolVersion DTLS1_0;
        static const ProtocolVersion DTLS1_2;
        static const ProtocolVersion DTLS1_3;

        static const ProtocolVersion SupportedProtocolVersions[];

        static constexpr bool isSupported(ProtocolVersion protocolVersion);

        friend bool operator==(const ProtocolVersion &lhs, const ProtocolVersion &rhs);
    };

    inline constexpr ProtocolVersion ProtocolVersion::DTLS1_0 = {254, 255};
    inline constexpr ProtocolVersion ProtocolVersion::DTLS1_2 = {254, 253};
    inline constexpr ProtocolVersion ProtocolVersion::DTLS1_3 = {254, 253}; // SAME AD 1.2! (https://datatracker.ietf.org/doc/html/rfc9147#section-5.3)

    inline constexpr ProtocolVersion ProtocolVersion::SupportedProtocolVersions[] = {ProtocolVersion::DTLS1_2};

    inline constexpr bool ProtocolVersion::isSupported(ProtocolVersion protocolVersion)
    {
        for (auto supportedProtocolVersion : SupportedProtocolVersions)
        {
            if (supportedProtocolVersion.major == protocolVersion.major && supportedProtocolVersion.minor == protocolVersion.minor)
                return true;
        }

        return false;
    }

    bool operator==(const ProtocolVersion &lhs, const ProtocolVersion &rhs)
    {
        return lhs.major == rhs.major && lhs.minor == lhs.minor;
    }
}