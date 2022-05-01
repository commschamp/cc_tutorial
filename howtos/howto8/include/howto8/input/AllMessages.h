// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "howto8/message/Msg1.h"
#include "howto8/message/Msg2.h"
#include "howto8/options/DefaultOptions.h"

namespace howto8
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto8::options::DefaultOptions>
using AllMessages =
    std::tuple<
        howto8::message::Msg1<TBase, TOpt>,
        howto8::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace howto8
