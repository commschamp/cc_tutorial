// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of <b>"Message"</b> interface class.

#pragma once

#include "comms/Message.h"
#include "comms/options.h"
#include "tutorial10/MsgId.h"

namespace tutorial10
{

/// @brief Definition of <b>"Message"</b> common interface class.
/// @tparam TOpt Interface definition options
/// @headerfile tutorial10/Message.h
template <typename... TOpt>
using Message =
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial10::MsgId>
    >;

} // namespace tutorial10
