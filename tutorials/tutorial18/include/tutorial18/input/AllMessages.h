// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of all messages bundle.

#pragma once

#include <tuple>
#include "tutorial18/message/Msg1_1.h"
#include "tutorial18/message/Msg1_2.h"
#include "tutorial18/message/Msg1_3.h"
#include "tutorial18/message/Msg2_1.h"
#include "tutorial18/message/Msg2_2.h"
#include "tutorial18/message/Msg2_3.h"
#include "tutorial18/options/DefaultOptions.h"

namespace tutorial18
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial18::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial18::message::Msg1_1<TBase, TOpt>,
        tutorial18::message::Msg1_2<TBase, TOpt>,
        tutorial18::message::Msg1_3<TBase, TOpt>,
        tutorial18::message::Msg2_1<TBase, TOpt>,
        tutorial18::message::Msg2_2<TBase, TOpt>,
        tutorial18::message::Msg2_3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial18


