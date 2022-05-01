// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto3/message/Msg1.h"
#include "howto3/message/Msg2.h"
#include "howto3/message/Msg3.h"
#include "howto3/options/DefaultOptions.h"

namespace howto3
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto3::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        howto3::message::Msg1<TBase, TOpt>,
        howto3::message::Msg2<TBase, TOpt>,
        howto3::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace howto3
