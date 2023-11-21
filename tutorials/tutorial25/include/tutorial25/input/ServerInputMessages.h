// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial25/message/Msg1.h"
#include "tutorial25/message/Msg10.h"
#include "tutorial25/message/Msg2.h"
#include "tutorial25/message/Msg3.h"
#include "tutorial25/message/Msg4.h"
#include "tutorial25/message/Msg5.h"
#include "tutorial25/message/Msg6.h"
#include "tutorial25/message/Msg7.h"
#include "tutorial25/message/Msg8.h"
#include "tutorial25/message/Msg9.h"
#include "tutorial25/options/DefaultOptions.h"

namespace tutorial25
{

namespace input
{

/// @brief Server input messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial25::options::DefaultOptions>
using ServerInputMessages =
    std::tuple<
        tutorial25::message::Msg1<TBase, TOpt>,
        tutorial25::message::Msg2<TBase, TOpt>,
        tutorial25::message::Msg3<TBase, TOpt>,
        tutorial25::message::Msg4<TBase, TOpt>,
        tutorial25::message::Msg5<TBase, TOpt>,
        tutorial25::message::Msg6<TBase, TOpt>,
        tutorial25::message::Msg7<TBase, TOpt>,
        tutorial25::message::Msg8<TBase, TOpt>,
        tutorial25::message::Msg9<TBase, TOpt>,
        tutorial25::message::Msg10<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial25

/// @brief Create type aliases for the server input messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL25_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = tutorial25::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = tutorial25::message::Msg2<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = tutorial25::message::Msg3<interface_, opts_>; \
    using prefix_ ## Msg4 ## suffix_ = tutorial25::message::Msg4<interface_, opts_>; \
    using prefix_ ## Msg5 ## suffix_ = tutorial25::message::Msg5<interface_, opts_>; \
    using prefix_ ## Msg6 ## suffix_ = tutorial25::message::Msg6<interface_, opts_>; \
    using prefix_ ## Msg7 ## suffix_ = tutorial25::message::Msg7<interface_, opts_>; \
    using prefix_ ## Msg8 ## suffix_ = tutorial25::message::Msg8<interface_, opts_>; \
    using prefix_ ## Msg9 ## suffix_ = tutorial25::message::Msg9<interface_, opts_>; \
    using prefix_ ## Msg10 ## suffix_ = tutorial25::message::Msg10<interface_, opts_>;

/// @brief Create type aliases for the server input messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL25_ALIASES_FOR_SERVER_INPUT_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL25_ALIASES_FOR_SERVER_INPUT_MESSAGES(prefix_, suffix_, interface_, tutorial25::options::DefaultOptions)
