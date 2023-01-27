// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial9/message/Msg1.h"
#include "tutorial9/message/Msg2.h"
#include "tutorial9/message/Msg3.h"
#include "tutorial9/message/Msg4.h"
#include "tutorial9/options/DefaultOptions.h"

namespace tutorial9
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial9::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial9::message::Msg1<TBase, TOpt>,
        tutorial9::message::Msg2<TBase, TOpt>,
        tutorial9::message::Msg3<TBase, TOpt>,
        tutorial9::message::Msg4<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial9
