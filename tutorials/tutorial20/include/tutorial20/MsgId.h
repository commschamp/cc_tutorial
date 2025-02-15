// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of message ids enumeration.

#pragma once

#include <cstdint>
#include "tutorial20/Version.h"

namespace tutorial20
{
/// @brief Message ids enumeration.
enum MsgId : std::uint8_t
{
    MsgId_Connect = 0, ///< message id of <b>Connect</b> message. 
    MsgId_M1 = 1, ///< message id of <b>Message 1</b> message. 
    MsgId_M2 = 2, ///< message id of <b>Message 2</b> message. 
    MsgId_M3 = 3, ///< message id of <b>Message 3</b> message. 

    // --- Extra values generated for convenience ---
    MsgId_FirstValue = 0, ///< First defined value.
    MsgId_LastValue = 3, ///< Last defined value.
    MsgId_ValuesLimit = 4, ///< Upper limit for defined values.
};

} // namespace tutorial20
