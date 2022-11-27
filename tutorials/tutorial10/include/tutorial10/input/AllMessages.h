// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial10/message/Msg1.h"
#include "tutorial10/message/Msg2.h"
#include "tutorial10/message/Msg3.h"
#include "tutorial10/message/Msg4.h"
#include "tutorial10/message/Msg5.h"
#include "tutorial10/options/DefaultOptions.h"

namespace tutorial10
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial10::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial10::message::Msg1<TBase, TOpt>,
        tutorial10::message::Msg2<TBase, TOpt>,
        tutorial10::message::Msg3<TBase, TOpt>,
        tutorial10::message::Msg4<TBase, TOpt>,
        tutorial10::message::Msg5<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial10
