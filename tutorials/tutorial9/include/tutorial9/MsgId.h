// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of message ids enumeration.

#pragma once

#include <cstdint>
#include "tutorial9/Version.h"

namespace tutorial9
{
/// @brief Message ids enumeration.
enum MsgId : std::uint8_t
{
    MsgId_M1 = 1, ///< message id of <b>Message 1</b> message. ,
    MsgId_M2 = 2, ///< message id of <b>Message 2</b> message. ,
    MsgId_M3 = 3, ///< message id of <b>Message 3</b> message. ,
    MsgId_M4 = 4, ///< message id of <b>Message 4</b> message. ,

    // --- Extra values generated for convenience ---,
    MsgId_FirstValue = 1, ///< First defined value.,
    MsgId_LastValue = 4, ///< Last defined value.,
    MsgId_ValuesLimit = 5, ///< Upper limit for defined values.
};

} // namespace tutorial9
