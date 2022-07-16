#pragma once

#include "AlertLevel.hpp"
#include "AlertDescription.hpp"

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.3

namespace crispy
{
    struct Alert
    {
        AlertLevel level;
        AlertDescription description;
    };
}