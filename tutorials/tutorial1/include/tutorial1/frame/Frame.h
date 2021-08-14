// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "tutorial1/field/FieldBase.h"
#include "tutorial1/field/MsgId.h"
#include "tutorial1/frame/FrameCommon.h"
#include "tutorial1/input/AllMessages.h"
#include "tutorial1/options/DefaultOptions.h"

namespace tutorial1
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile "tutorial1/frame/Frame.h"
template <typename TOpt = tutorial1::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;
    
    /// @brief Scope for field(s) of @ref ID layer.
    struct IDMembers
    {
        /// @brief Definition of <b>"MsgId"</b> field.
        using MsgId =
            tutorial1::field::MsgId<
                TOpt
            >;
        
    };
    
    /// @brief Definition of layer "ID".
    template <typename TMessage, typename TAllMessages>
    using ID =
        comms::protocol::MsgIdLayer<
            typename IDMembers::MsgId,
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
/// @headerfile "tutorial1/frame/Frame.h"
template <
   typename TMessage,
   typename TAllMessages = tutorial1::input::AllMessages<TMessage>,
   typename TOpt = tutorial1::options::DefaultOptions
>
class Frame : public
    FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base =
        typename FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    /// @brief Allow access to frame definition layers.
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_ACCESS macro
    ///     from COMMS library for details.
    ///
    ///     The generated functions are:
    ///     @li layer_data() for @ref FrameLayers::Data layer.
    ///     @li layer_iD() for @ref FrameLayers::ID layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        iD
    );
};

} // namespace frame

} // namespace tutorial1


