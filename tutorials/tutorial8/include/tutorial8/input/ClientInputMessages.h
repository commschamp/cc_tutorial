// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial8/message/Msg1.h"
#include "tutorial8/message/Msg2.h"
#include "tutorial8/message/Msg3.h"
#include "tutorial8/options/DefaultOptions.h"

namespace tutorial8
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial8::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        tutorial8::message::Msg1<TBase, TOpt>,
        tutorial8::message::Msg2<TBase, TOpt>,
        tutorial8::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial8
