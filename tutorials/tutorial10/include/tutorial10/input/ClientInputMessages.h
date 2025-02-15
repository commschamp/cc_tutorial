// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of the ClientInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial10/message/Msg2.h"
#include "tutorial10/message/Msg3.h"
#include "tutorial10/message/Msg4.h"
#include "tutorial10/message/Msg5.h"
#include "tutorial10/options/DefaultOptions.h"

namespace tutorial10
{

namespace input
{

/// @brief Client input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial10::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        tutorial10::message::Msg2<TBase, TOpt>,
        tutorial10::message::Msg3<TBase, TOpt>,
        tutorial10::message::Msg4<TBase, TOpt>,
        tutorial10::message::Msg5<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial10

/// @brief Create type aliases for the client input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL10_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg2 ## suffix_ = tutorial10::message::Msg2<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = tutorial10::message::Msg3<interface_, opts_>; \
    using prefix_ ## Msg4 ## suffix_ = tutorial10::message::Msg4<interface_, opts_>; \
    using prefix_ ## Msg5 ## suffix_ = tutorial10::message::Msg5<interface_, opts_>;

/// @brief Create type aliases for the client input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL10_ALIASES_FOR_CLIENT_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL10_ALIASES_FOR_CLIENT_INPUT_MESSAGES(prefix_, suffix_, interface_, tutorial10::options::DefaultOptions)
