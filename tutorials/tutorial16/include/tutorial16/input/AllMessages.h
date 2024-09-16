// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial16/message/Msg1.h"
#include "tutorial16/message/Msg2.h"
#include "tutorial16/message/Msg3.h"
#include "tutorial16/message/Msg4.h"
#include "tutorial16/options/DefaultOptions.h"

namespace tutorial16
{

namespace input
{

/// @brief All messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial16::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial16::message::Msg1<TBase, TOpt>,
        tutorial16::message::Msg2<TBase, TOpt>,
        tutorial16::message::Msg3<TBase, TOpt>,
        tutorial16::message::Msg4<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial16

/// @brief Create type aliases for the all messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL16_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = tutorial16::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = tutorial16::message::Msg2<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = tutorial16::message::Msg3<interface_, opts_>; \
    using prefix_ ## Msg4 ## suffix_ = tutorial16::message::Msg4<interface_, opts_>;

/// @brief Create type aliases for the all messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL16_ALIASES_FOR_ALL_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL16_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, tutorial16::options::DefaultOptions)
