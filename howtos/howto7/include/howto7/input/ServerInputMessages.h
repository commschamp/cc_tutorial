// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto7/message/Msg1.h"
#include "howto7/message/Msg2.h"
#include "howto7/message/Msg3.h"
#include "howto7/options/DefaultOptions.h"

namespace howto7
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto7::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        howto7::message::Msg1<TBase, TOpt>,
        howto7::message::Msg2<TBase, TOpt>,
        howto7::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace howto7
