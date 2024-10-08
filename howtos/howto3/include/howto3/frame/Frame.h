// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "howto3/field/MsgId.h"
#include "howto3/input/AllMessages.h"
#include "howto3/options/DefaultOptions.h"

namespace howto3
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto3/frame/Frame.h
template <typename TOpt = howto3::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            howto3::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Id<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile howto3/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto3::input::AllMessages<TMessage>,
   typename TOpt = howto3::options::DefaultOptions
>
class Frame : public
    FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base = typename
        FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    /// @brief Allow access to frame definition layers.
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_NAMES macro
    ///     from COMMS library for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Layer_data type and @b layer_data() function
    ///         for @ref FrameLayers::Data layer.
    ///     @li @b Layer_id type and @b layer_id() function
    ///         for @ref FrameLayers::Id layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        id
    );
};

} // namespace frame

} // namespace howto3
