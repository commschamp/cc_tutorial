// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL9_SPEC_VERSION (0U)

namespace tutorial9
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL9_SPEC_VERSION;
}

} // namespace tutorial9

// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(5, 0, 3) <= comms::version(),
    "The version of COMMS library is too old");
