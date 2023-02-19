// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial6/message/Msg1.h"
#include "tutorial6/message/Msg2.h"
#include "tutorial6/message/Msg3.h"
#include "tutorial6/options/DefaultOptions.h"

namespace tutorial6
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial6::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        tutorial6::message::Msg1<TBase, TOpt>,
        tutorial6::message::Msg2<TBase, TOpt>,
        tutorial6::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial6
