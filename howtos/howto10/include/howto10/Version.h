// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define HOWTO10_SPEC_VERSION (0U)

namespace howto10
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return HOWTO10_SPEC_VERSION;
}

} // namespace howto10


// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(3, 4, 0) <= comms::version(),
    "The version of COMMS library is too old");

