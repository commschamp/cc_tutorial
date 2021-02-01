// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of all client input messages bundle.

#pragma once

#include <tuple>
#include "howto1/message/Msg1.h"
#include "howto1/message/Msg2.h"
#include "howto1/options/DefaultOptions.h"

namespace howto1
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto1::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto1::message::Msg1<TBase, TOpt>,
        howto1::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace howto1


