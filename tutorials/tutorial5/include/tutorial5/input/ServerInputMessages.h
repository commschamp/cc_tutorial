// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial5/message/Msg1.h"
#include "tutorial5/message/Msg2.h"
#include "tutorial5/message/Msg3.h"
#include "tutorial5/options/DefaultOptions.h"

namespace tutorial5
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial5::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        tutorial5::message::Msg1<TBase, TOpt>,
        tutorial5::message::Msg2<TBase, TOpt>,
        tutorial5::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial5
