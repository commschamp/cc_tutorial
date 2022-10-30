// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial23/message/Msg1.h"
#include "tutorial23/options/DefaultOptions.h"

namespace tutorial23
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial23::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        tutorial23::message::Msg1<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial23
