// Generated by commsdsl2comms v3.3.1

/// @file
/// @brief Contains definition of message ids enumeration.

#pragma once

#include <cstdint>
#include "tutorial2/Version.h"

namespace tutorial2
{

/// @brief Message ids enumeration.
enum MsgId : std::uint8_t
{
    MsgId_M1 = 1, ///< message id of @b M1 message.
    MsgId_M2 = 2, ///< message id of @b M2 message.
    MsgId_M3 = 3, ///< message id of @b M3 message.
    MsgId_M4 = 4, ///< message id of @b M4 message.
    MsgId_M5 = 5, ///< message id of @b M5 message.
    MsgId_M6 = 6, ///< message id of @b M6 message.
    MsgId_M7 = 7, ///< message id of @b M7 message.
    
    // --- Extra values generated for convenience ---
    MsgId_FirstValue = 1, ///< First defined value.
    MsgId_LastValue = 7, ///< Last defined value.
    MsgId_ValuesLimit = 8, ///< Upper limit for defined values.
    
};

} // namespace tutorial2

