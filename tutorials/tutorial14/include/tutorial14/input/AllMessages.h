// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of all messages bundle.

#pragma once

#include <tuple>
#include "tutorial14/message/Msg1.h"
#include "tutorial14/message/Msg2.h"
#include "tutorial14/options/DefaultOptions.h"

namespace tutorial14
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial14::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial14::message::Msg1<TBase, TOpt>,
        tutorial14::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial14


