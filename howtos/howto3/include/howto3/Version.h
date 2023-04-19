// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define HOWTO3_SPEC_VERSION (0U)

namespace howto3
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return HOWTO3_SPEC_VERSION;
}

} // namespace howto3

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 2, 0) <= comms::version(),
    "The version of COMMS library is too old");
