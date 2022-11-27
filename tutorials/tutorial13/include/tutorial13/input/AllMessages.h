// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial13/message/Msg1_1.h"
#include "tutorial13/message/Msg1_2.h"
#include "tutorial13/message/Msg1_3.h"
#include "tutorial13/message/Msg2_1.h"
#include "tutorial13/message/Msg2_2.h"
#include "tutorial13/message/Msg2_3.h"
#include "tutorial13/options/DefaultOptions.h"

namespace tutorial13
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial13::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial13::message::Msg1_1<TBase, TOpt>,
        tutorial13::message::Msg1_2<TBase, TOpt>,
        tutorial13::message::Msg1_3<TBase, TOpt>,
        tutorial13::message::Msg2_1<TBase, TOpt>,
        tutorial13::message::Msg2_2<TBase, TOpt>,
        tutorial13::message::Msg2_3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial13
