// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto9/message/Msg1.h"
#include "howto9/message/Msg2.h"
#include "howto9/message/Msg3.h"
#include "howto9/options/DefaultOptions.h"

namespace howto9
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto9::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto9::message::Msg1<TBase, TOpt>,
        howto9::message::Msg2<TBase, TOpt>,
        howto9::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace howto9
