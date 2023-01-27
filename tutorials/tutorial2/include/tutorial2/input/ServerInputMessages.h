// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains definition of the ServerInputMessages messages bundle.

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

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial2::options::DefaultOptions>
using ServerInputMessages =
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
        tutorial2::message::Msg17<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial2
