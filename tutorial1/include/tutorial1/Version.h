/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TUTORIAL1_SPEC_VERSION (0U)

namespace tutorial1
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TUTORIAL1_SPEC_VERSION;
}

} // namespace tutorial1


// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(2, 2, 1) <= comms::version(),
    "The version of COMMS library is too old");

