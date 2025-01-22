// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto5/message/Msg1.h"
#include "howto5/message/Msg2.h"
#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace input
{

/// @brief Server input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto5::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        howto5::message::Msg1<TBase, TOpt>,
        howto5::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace howto5

/// @brief Create type aliases for the server input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define HOWTO5_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = howto5::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = howto5::message::Msg2<interface_, opts_>;

/// @brief Create type aliases for the server input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define HOWTO5_ALIASES_FOR_SERVER_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    HOWTO5_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, howto5::options::DefaultOptions)
