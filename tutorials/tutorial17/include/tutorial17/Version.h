// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL17_SPEC_VERSION (0U)

namespace tutorial17
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL17_SPEC_VERSION;
}

} // namespace tutorial17

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 0, 2) <= comms::version(),
    "The version of COMMS library is too old");
