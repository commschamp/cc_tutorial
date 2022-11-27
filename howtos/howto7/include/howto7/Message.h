// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of <b>"Message"</b> interface class.

#pragma once

#include "comms/Message.h"
#include "comms/options.h"
#include "howto7/MsgId.h"

namespace howto7
{

/// @brief Definition of <b>"Message"</b> common interface class.
/// @tparam TOpt Interface definition options
/// @headerfile howto7/Message.h
template <typename... TOpt>
using Message =
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<howto7::MsgId>
    >;

} // namespace howto7
