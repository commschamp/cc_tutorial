// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL13_SPEC_VERSION (0U)

namespace tutorial13
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL13_SPEC_VERSION;
}

} // namespace tutorial13

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 0, 3) <= comms::version(),
    "The version of COMMS library is too old");
