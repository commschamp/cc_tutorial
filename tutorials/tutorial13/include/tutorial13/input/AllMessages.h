// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial13/message/Msg1_1.h"
#include "tutorial13/message/Msg1_2.h"
#include "tutorial13/message/Msg1_3.h"
#include "tutorial13/message/Msg2_1.h"
#include "tutorial13/message/Msg2_2.h"
#include "tutorial13/message/Msg2_3.h"
#include "tutorial13/options/DefaultOptions.h"

namespace tutorial13
{

namespace input
{

/// @brief All messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial13::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial13::message::Msg1_1<TBase, TOpt>,
        tutorial13::message::Msg1_2<TBase, TOpt>,
        tutorial13::message::Msg1_3<TBase, TOpt>,
        tutorial13::message::Msg2_1<TBase, TOpt>,
        tutorial13::message::Msg2_2<TBase, TOpt>,
        tutorial13::message::Msg2_3<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial13

/// @brief Create type aliases for the all messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL13_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1_1 ## suffix_ = tutorial13::message::Msg1_1<interface_, opts_>; \
    using prefix_ ## Msg1_2 ## suffix_ = tutorial13::message::Msg1_2<interface_, opts_>; \
    using prefix_ ## Msg1_3 ## suffix_ = tutorial13::message::Msg1_3<interface_, opts_>; \
    using prefix_ ## Msg2_1 ## suffix_ = tutorial13::message::Msg2_1<interface_, opts_>; \
    using prefix_ ## Msg2_2 ## suffix_ = tutorial13::message::Msg2_2<interface_, opts_>; \
    using prefix_ ## Msg2_3 ## suffix_ = tutorial13::message::Msg2_3<interface_, opts_>;

/// @brief Create type aliases for the all messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL13_ALIASES_FOR_ALL_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL13_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, tutorial13::options::DefaultOptions)
