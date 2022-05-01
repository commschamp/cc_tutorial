// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL4_SPEC_VERSION (0U)

namespace tutorial4
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL4_SPEC_VERSION;
}

} // namespace tutorial4

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(4, 0, 0) <= comms::version(),
    "The version of COMMS library is too old");

