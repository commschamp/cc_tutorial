// Generated by commsdsl2comms v3.3.1

/// @file
/// @brief Contains definition of all server input messages bundle.

#pragma once

#include <tuple>
#include "tutorial2/message/Msg1.h"
#include "tutorial2/message/Msg2.h"
#include "tutorial2/message/Msg3.h"
#include "tutorial2/message/Msg4.h"
#include "tutorial2/message/Msg5.h"
#include "tutorial2/message/Msg6.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial2::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        tutorial2::message::Msg1<TBase, TOpt>,
        tutorial2::message::Msg2<TBase, TOpt>,
        tutorial2::message::Msg3<TBase, TOpt>,
        tutorial2::message::Msg4<TBase, TOpt>,
        tutorial2::message::Msg5<TBase, TOpt>,
        tutorial2::message::Msg6<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial2


