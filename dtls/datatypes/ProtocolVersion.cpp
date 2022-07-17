#include "ProtocolVersion.hpp"

#include <sstream>

namespace crispy
{
    inline constexpr ProtocolVersion ProtocolVersion::DTLS1_0 = { 254, 255 };
    inline constexpr ProtocolVersion ProtocolVersion::DTLS1_2 = { 254, 253 };
    inline constexpr ProtocolVersion ProtocolVersion::DTLS1_3 = { 254, 253 }; // SAME AD 1.2! (https://datatracker.ietf.org/doc/html/rfc9147#section-5.3)

    inline constexpr ProtocolVersion ProtocolVersion::SupportedProtocolVersions[] = { ProtocolVersion::DTLS1_2 };

    std::string ProtocolVersion::toString() const
    {
        std::ostringstream oss;
        oss << "ProtocolVersion: { " << static_cast<std::uint32_t>(this->major) << ", " << static_cast<std::uint32_t>(this->minor) << " }" << std::endl;
        return oss.str();
    }

    inline constexpr bool ProtocolVersion::isSupported(ProtocolVersion protocolVersion)
    {
        for (auto supportedProtocolVersion : SupportedProtocolVersions)
        {
            if (supportedProtocolVersion == protocolVersion)
                return true;
        }

        return false;
    }

    bool operator==(const ProtocolVersion& lhs, const ProtocolVersion& rhs)
    {
        return lhs.major == rhs.major && lhs.minor == lhs.minor;
    }
}