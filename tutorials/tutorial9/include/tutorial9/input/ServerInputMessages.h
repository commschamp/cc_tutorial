// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial9/message/Msg1.h"
#include "tutorial9/message/Msg3.h"
#include "tutorial9/options/DefaultOptions.h"

namespace tutorial9
{

namespace input
{

/// @brief Server input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial9::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        tutorial9::message::Msg1<TBase, TOpt>,
        tutorial9::message::Msg3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial9

/// @brief Create type aliases for the server input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL9_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = tutorial9::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = tutorial9::message::Msg3<interface_, opts_>;

/// @brief Create type aliases for the server input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL9_ALIASES_FOR_SERVER_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL9_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, tutorial9::options::DefaultOptions)
