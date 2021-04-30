// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains definition of all client input messages bundle.

#pragma once

#include <tuple>
#include "howto6/message/Msg1.h"
#include "howto6/message/Msg2.h"
#include "howto6/message/Msg3.h"
#include "howto6/options/DefaultOptions.h"

namespace howto6
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto6::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto6::message::Msg1<TBase, TOpt>,
        howto6::message::Msg2<TBase, TOpt>,
        howto6::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace howto6


