// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL10_SPEC_VERSION (0U)

namespace tutorial10
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL10_SPEC_VERSION;
}

} // namespace tutorial10

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(4, 0, 0) <= comms::version(),
    "The version of COMMS library is too old");

