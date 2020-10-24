// Generated by commsdsl2comms v3.5.3

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL18_SPEC_VERSION (0U)

namespace tutorial18
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL18_SPEC_VERSION;
}

} // namespace tutorial18


// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(3, 1, 0) <= comms::version(),
    "The version of COMMS library is too old");

