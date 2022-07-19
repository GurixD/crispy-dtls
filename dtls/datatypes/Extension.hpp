#pragma once

#include "ExtensionType.hpp"
#include "../bigendian/integer.hpp"
#include <cstddef>
#include <vector>
#include <string>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace crispy
{
    struct Extension
    {
        // ExtensionType extension_type;
        bigendian::uint16 extension_type;
        bigendian::uint16 extension_data_length; // <0..2 ^ 16 - 1>
        std::vector<std::byte> extension_data;

        std::string toString() const;

        static const ExtensionType SupportedExtensions[];
        static const ExtensionType RecommandedExtensions[];
        static bool isSupported(ExtensionType extension);
        static bool isRecommanded(ExtensionType extension);
    };
}