// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"Message"</b> interface class.

#pragma once

#include "comms/Message.h"
#include "comms/options.h"
#include "tutorial22/MsgId.h"

namespace tutorial22
{

/// @brief Definition of <b>"Message"</b> common interface class.
/// @tparam TOpt Interface definition options
/// @headerfile tutorial22/Message.h
template <typename... TOpt>
using Message =
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial22::MsgId>
    >;

} // namespace tutorial22
