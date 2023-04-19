// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL11_SPEC_VERSION (0U)

namespace tutorial11
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL11_SPEC_VERSION;
}

} // namespace tutorial11

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 2, 0) <= comms::version(),
    "The version of COMMS library is too old");
