// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto2/message/Msg1.h"
#include "howto2/message/Msg2.h"
#include "howto2/message/Msg3.h"
#include "howto2/message/Msg4.h"
#include "howto2/options/DefaultOptions.h"

namespace howto2
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto2::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        howto2::message::Msg1<TBase, TOpt>,
        howto2::message::Msg2<TBase, TOpt>,
        howto2::message::Msg3<TBase, TOpt>,
        howto2::message::Msg4<TBase, TOpt>
    >;

} // namespace input

} // namespace howto2
