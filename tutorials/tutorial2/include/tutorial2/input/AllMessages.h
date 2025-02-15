// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of the AllMessages messages bundle.

#pragma once

#include <tuple>
#include "tutorial2/message/Msg1.h"
#include "tutorial2/message/Msg10.h"
#include "tutorial2/message/Msg11.h"
#include "tutorial2/message/Msg12.h"
#include "tutorial2/message/Msg13.h"
#include "tutorial2/message/Msg14.h"
#include "tutorial2/message/Msg15.h"
#include "tutorial2/message/Msg16.h"
#include "tutorial2/message/Msg17.h"
#include "tutorial2/message/Msg18.h"
#include "tutorial2/message/Msg2.h"
#include "tutorial2/message/Msg3.h"
#include "tutorial2/message/Msg4.h"
#include "tutorial2/message/Msg5.h"
#include "tutorial2/message/Msg6.h"
#include "tutorial2/message/Msg7.h"
#include "tutorial2/message/Msg8.h"
#include "tutorial2/message/Msg9.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace input
{

/// @brief All messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial2::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial2::message::Msg1<TBase, TOpt>,
        tutorial2::message::Msg2<TBase, TOpt>,
        tutorial2::message::Msg3<TBase, TOpt>,
        tutorial2::message::Msg4<TBase, TOpt>,
        tutorial2::message::Msg5<TBase, TOpt>,
        tutorial2::message::Msg6<TBase, TOpt>,
        tutorial2::message::Msg7<TBase, TOpt>,
        tutorial2::message::Msg8<TBase, TOpt>,
        tutorial2::message::Msg9<TBase, TOpt>,
        tutorial2::message::Msg10<TBase, TOpt>,
        tutorial2::message::Msg11<TBase, TOpt>,
        tutorial2::message::Msg12<TBase, TOpt>,
        tutorial2::message::Msg13<TBase, TOpt>,
        tutorial2::message::Msg14<TBase, TOpt>,
        tutorial2::message::Msg15<TBase, TOpt>,
        tutorial2::message::Msg16<TBase, TOpt>,
        tutorial2::message::Msg17<TBase, TOpt>,
        tutorial2::message::Msg18<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial2

/// @brief Create type aliases for the all messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL2_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = tutorial2::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = tutorial2::message::Msg2<interface_, opts_>; \
    using prefix_ ## Msg3 ## suffix_ = tutorial2::message::Msg3<interface_, opts_>; \
    using prefix_ ## Msg4 ## suffix_ = tutorial2::message::Msg4<interface_, opts_>; \
    using prefix_ ## Msg5 ## suffix_ = tutorial2::message::Msg5<interface_, opts_>; \
    using prefix_ ## Msg6 ## suffix_ = tutorial2::message::Msg6<interface_, opts_>; \
    using prefix_ ## Msg7 ## suffix_ = tutorial2::message::Msg7<interface_, opts_>; \
    using prefix_ ## Msg8 ## suffix_ = tutorial2::message::Msg8<interface_, opts_>; \
    using prefix_ ## Msg9 ## suffix_ = tutorial2::message::Msg9<interface_, opts_>; \
    using prefix_ ## Msg10 ## suffix_ = tutorial2::message::Msg10<interface_, opts_>; \
    using prefix_ ## Msg11 ## suffix_ = tutorial2::message::Msg11<interface_, opts_>; \
    using prefix_ ## Msg12 ## suffix_ = tutorial2::message::Msg12<interface_, opts_>; \
    using prefix_ ## Msg13 ## suffix_ = tutorial2::message::Msg13<interface_, opts_>; \
    using prefix_ ## Msg14 ## suffix_ = tutorial2::message::Msg14<interface_, opts_>; \
    using prefix_ ## Msg15 ## suffix_ = tutorial2::message::Msg15<interface_, opts_>; \
    using prefix_ ## Msg16 ## suffix_ = tutorial2::message::Msg16<interface_, opts_>; \
    using prefix_ ## Msg17 ## suffix_ = tutorial2::message::Msg17<interface_, opts_>; \
    using prefix_ ## Msg18 ## suffix_ = tutorial2::message::Msg18<interface_, opts_>;

/// @brief Create type aliases for the all messages of the protocol using default options.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
#define TUTORIAL2_ALIASES_FOR_ALL_MESSAGES_DEFAULT_OPTIONS(prefix_, suffix_, interface_) \
    TUTORIAL2_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, tutorial2::options::DefaultOptions)
