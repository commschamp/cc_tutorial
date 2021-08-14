// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of <b>"ServerToClientFrame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "tutorial5/field/FieldBase.h"
#include "tutorial5/field/MsgId.h"
#include "tutorial5/frame/ServerToClientFrameCommon.h"
#include "tutorial5/input/AllMessages.h"
#include "tutorial5/options/DefaultOptions.h"

namespace tutorial5
{

namespace frame
{

/// @brief Layers definition of @ref ServerToClientFrame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref ServerToClientFrame
/// @headerfile "tutorial5/frame/ServerToClientFrame.h"
template <typename TOpt = tutorial5::options::DefaultOptions>
struct ServerToClientFrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::ServerToClientFrameLayers::Data
        >;
    
    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            tutorial5::field::MsgId<TOpt>,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::ServerToClientFrameLayers::Id
        >;
    
    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        struct SizeField : public
            comms::field::IntValue<
                tutorial5::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial5::frame::ServerToClientFrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
            }
            
        };
        
    };
    
    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            typename SizeMembers::SizeField,
            Id<TMessage, TAllMessages>
        >;
    
    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Size<TMessage, TAllMessages>;
    
};

/// @brief Definition of <b>"ServerToClientFrame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile "tutorial5/frame/ServerToClientFrame.h"
template <
   typename TMessage,
   typename TAllMessages = tutorial5::input::AllMessages<TMessage>,
   typename TOpt = tutorial5::options::DefaultOptions
>
class ServerToClientFrame : public
    ServerToClientFrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base =
        typename ServerToClientFrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    /// @brief Allow access to frame definition layers.
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_ACCESS macro
    ///     from COMMS library for details.
    ///
    ///     The generated functions are:
    ///     @li layer_data() for @ref ServerToClientFrameLayers::Data layer.
    ///     @li layer_id() for @ref ServerToClientFrameLayers::Id layer.
    ///     @li layer_size() for @ref ServerToClientFrameLayers::Size layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        id,
        size
    );
};

} // namespace frame

} // namespace tutorial5


