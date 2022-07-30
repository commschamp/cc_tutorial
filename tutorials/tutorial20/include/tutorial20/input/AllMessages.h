// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial20/message/Connect.h"
#include "tutorial20/message/Msg1.h"
#include "tutorial20/message/Msg2.h"
#include "tutorial20/message/Msg3.h"
#include "tutorial20/options/DefaultOptions.h"

namespace tutorial20
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial20::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial20::message::Connect<TBase, TOpt>,
        tutorial20::message::Msg1<TBase, TOpt>,
        tutorial20::message::Msg2<TBase, TOpt>,
        tutorial20::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial20
