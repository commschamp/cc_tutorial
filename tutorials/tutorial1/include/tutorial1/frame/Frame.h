// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "tutorial1/field/MsgId.h"
#include "tutorial1/input/AllMessages.h"
#include "tutorial1/options/DefaultOptions.h"

namespace tutorial1
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial1/frame/Frame.h
template <typename TOpt = tutorial1::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;

    /// @brief Definition of layer "ID".
    template <typename TMessage, typename TAllMessages>
    using ID =
        comms::protocol::MsgIdLayer<
            tutorial1::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::ID
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = ID<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial1/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial1::input::AllMessages<TMessage>,
   typename TOpt = tutorial1::options::DefaultOptions
>
class Frame : public
    FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base = typename
        FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    /// @brief Allow access to frame definition layers.
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_ACCESS macro
    ///     from COMMS library for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Layer_data type and @b layer_data() function
    ///         for @ref FrameLayers::Data layer.
    ///     @li @b Layer_iD type and @b layer_iD() function
    ///         for @ref FrameLayers::ID layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        iD
    );
};

} // namespace frame

} // namespace tutorial1
