// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define HOWTO4_SPEC_VERSION (0U)

namespace howto4
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return HOWTO4_SPEC_VERSION;
}

} // namespace howto4

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 2, 1) <= comms::version(),
    "The version of COMMS library is too old");
