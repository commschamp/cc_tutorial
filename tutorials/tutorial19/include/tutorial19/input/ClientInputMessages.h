// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial19/message/Msg1.h"
#include "tutorial19/message/Msg2.h"
#include "tutorial19/message/Msg3.h"
#include "tutorial19/options/DefaultOptions.h"

namespace tutorial19
{

namespace input
{

/// @brief Client input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial19::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        tutorial19::message::Msg1<TBase, TOpt>,
        tutorial19::message::Msg2<TBase, TOpt>,
        tutorial19::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial19

/// @brief Create type aliases for the client input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL19_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = tutorial19::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = tutorial19::message::Msg2<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = tutorial19::message::Msg3<interface_, opts_>;

/// @brief Create type aliases for the client input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL19_ALIASES_FOR_CLIENT_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL19_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, tutorial19::options::DefaultOptions)
