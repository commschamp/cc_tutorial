// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial21/message/Msg1.h"
#include "tutorial21/message/Msg2.h"
#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial21::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial21::message::Msg1<TBase, TOpt>,
        tutorial21::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial21
