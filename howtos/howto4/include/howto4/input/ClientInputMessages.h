// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto4/message/Msg.h"
#include "howto4/options/DefaultOptions.h"

namespace howto4
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto4::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto4::message::Msg<TBase, TOpt>
    >;

} // namespace input

} // namespace howto4
