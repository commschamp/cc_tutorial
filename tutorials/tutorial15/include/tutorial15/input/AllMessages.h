// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial15/message/Msg1.h"
#include "tutorial15/message/Msg2.h"
#include "tutorial15/message/Msg3.h"
#include "tutorial15/options/DefaultOptions.h"

namespace tutorial15
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial15::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial15::message::Msg1<TBase, TOpt>,
        tutorial15::message::Msg2<TBase, TOpt>,
        tutorial15::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial15
