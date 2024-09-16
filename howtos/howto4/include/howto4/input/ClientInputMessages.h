// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "howto4/message/Msg.h"
#include "howto4/options/DefaultOptions.h"

namespace howto4
{

namespace input
{

/// @brief Client input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = howto4::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        howto4::message::Msg<TBase, TOpt>
    >;

} // namespace input

} // namespace howto4

/// @brief Create type aliases for the client input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define HOWTO4_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg ## suffix_ = howto4::message::Msg<interface_, opts_>;

/// @brief Create type aliases for the client input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define HOWTO4_ALIASES_FOR_CLIENT_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    HOWTO4_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, howto4::options::DefaultOptions)
