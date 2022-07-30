// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define HOWTO5_SPEC_VERSION (5U)

namespace howto5
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return HOWTO5_SPEC_VERSION;
}

} // namespace howto5

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 0, 0) <= comms::version(),
    "The version of COMMS library is too old");

