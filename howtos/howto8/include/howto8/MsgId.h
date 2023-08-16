// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of message ids enumeration.

#pragma once

#include <cstdint>
#include "howto8/Version.h"

namespace howto8
{
/// @brief Message ids enumeration.
enum MsgId : std::uint8_t
{
    MsgId_M1 = 1, ///< message id of <b>Message 1</b> message. 
    MsgId_M2 = 2, ///< message id of <b>Message 2</b> message. 

    // --- Extra values generated for convenience ---
    MsgId_FirstValue = 1, ///< First defined value.
    MsgId_LastValue = 2, ///< Last defined value.
    MsgId_ValuesLimit = 3, ///< Upper limit for defined values.
};

} // namespace howto8
