// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto6/message/Msg1.h"
#include "howto6/message/Msg2.h"
#include "howto6/message/Msg3.h"
#include "howto6/options/DefaultOptions.h"

namespace howto6
{

namespace input
{

/// @brief Server input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto6::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        howto6::message::Msg1<TBase, TOpt>,
        howto6::message::Msg2<TBase, TOpt>,
        howto6::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace howto6

/// @brief Create type aliases for the server input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define HOWTO6_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = howto6::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = howto6::message::Msg2<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = howto6::message::Msg3<interface_, opts_>;

/// @brief Create type aliases for the server input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define HOWTO6_ALIASES_FOR_SERVER_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    HOWTO6_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, howto6::options::DefaultOptions)
