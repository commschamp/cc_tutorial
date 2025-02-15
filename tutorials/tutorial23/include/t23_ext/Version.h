// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define T23_EXT_SPEC_VERSION (0U)

namespace t23_ext
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return T23_EXT_SPEC_VERSION;
}

} // namespace t23_ext

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 3, 0) <= comms::version(),
    "The version of COMMS library is too old");
