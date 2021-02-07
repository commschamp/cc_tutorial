// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"Message"</b> interface class.

#pragma once

#include "comms/Message.h"
#include "comms/options.h"
#include "howto2/MsgId.h"

namespace howto2
{

/// @brief Definition of <b>"Message"</b> common interface class.
/// @tparam TOpt Interface definition options
/// @headerfile "howto2/Message.h"
template <typename... TOpt>
using Message =
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<howto2::MsgId>
    >;

} // namespace howto2


