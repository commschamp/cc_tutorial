// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto1/message/Msg1.h"
#include "howto1/message/Msg2.h"
#include "howto1/options/DefaultOptions.h"

namespace howto1
{

namespace input
{

/// @brief Client input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto1::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto1::message::Msg1<TBase, TOpt>,
        howto1::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace howto1

/// @brief Create type aliases for the client input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define HOWTO1_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = howto1::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = howto1::message::Msg2<interface_, opts_>;

/// @brief Create type aliases for the client input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define HOWTO1_ALIASES_FOR_CLIENT_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    HOWTO1_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, howto1::options::DefaultOptions)
