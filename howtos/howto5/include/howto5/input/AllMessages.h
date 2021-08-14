// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of all messages bundle.

#pragma once

#include <tuple>
#include "howto5/message/Msg1.h"
#include "howto5/message/Msg2.h"
#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto5::options::DefaultOptions>
using AllMessages =
    std::tuple<
        howto5::message::Msg1<TBase, TOpt>,
        howto5::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace howto5


