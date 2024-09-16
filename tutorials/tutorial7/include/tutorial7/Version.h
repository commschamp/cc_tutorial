// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL7_SPEC_VERSION (0U)

namespace tutorial7
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL7_SPEC_VERSION;
}

} // namespace tutorial7

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 2, 7) <= comms::version(),
    "The version of COMMS library is too old");
