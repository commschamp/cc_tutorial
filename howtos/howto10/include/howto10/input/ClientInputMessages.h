// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto10/message/Msg1.h"
#include "howto10/message/Msg2.h"
#include "howto10/message/Msg3.h"
#include "howto10/options/DefaultOptions.h"

namespace howto10
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto10::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto10::message::Msg1<TBase, TOpt>,
        howto10::message::Msg2<TBase, TOpt>,
        howto10::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace howto10
