// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "comms/protocol/SyncPrefixLayer.h"
#include "comms/protocol/TransportValueLayer.h"
#include "howto6/field/ChecksumType.h"
#include "howto6/field/FieldBase.h"
#include "howto6/field/MsgId.h"
#include "howto6/frame/FrameCommon.h"
#include "howto6/frame/layer/Checksum.h"
#include "howto6/input/AllMessages.h"
#include "howto6/options/DefaultOptions.h"

namespace howto6
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile "howto6/frame/Frame.h"
template <typename TOpt = howto6::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;
    
    /// @brief Definition of layer "ChekcusmType".
    using ChekcusmType =
        comms::protocol::TransportValueLayer<
            howto6::field::ChecksumType<TOpt>,
            0U,
            Data
        >;
    
    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            howto6::field::MsgId<TOpt>,
            TMessage,
            TAllMessages,
            ChekcusmType,
            typename TOpt::frame::FrameLayers::Id
        >;
    
    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        struct SizeField : public
            comms::field::IntValue<
                howto6::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return howto6::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
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
    
    /// @brief Scope for field(s) of @ref Sync layer.
    struct SyncMembers
    {
        /// @brief Definition of <b>"SyncField"</b> field.
        struct SyncField : public
            comms::field::IntValue<
                howto6::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                comms::option::def::DefaultNumValue<43981L>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return howto6::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::name();
            }
            
        };
        
    };
    
    /// @brief Definition of layer "Sync".
    template <typename TMessage, typename TAllMessages>
    using Sync =
        comms::protocol::SyncPrefixLayer<
            typename SyncMembers::SyncField,
            Size<TMessage, TAllMessages>
        >;
    
    /// @brief Scope for field(s) of @ref Checksum layer.
    struct ChecksumMembers
    {
        /// @brief Definition of <b>"ChecksumField"</b> field.
        struct ChecksumField : public
            comms::field::IntValue<
                howto6::field::FieldBase<>,
                std::uint32_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return howto6::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::name();
            }
            
        };
        
    };
    
    /// @brief Definition of layer "Checksum".
    template <typename TMessage, typename TAllMessages>
    using Checksum =
        howto6::frame::layer::Checksum<
            typename ChecksumMembers::ChecksumField,
            Sync<TMessage, TAllMessages>,
            typename TOpt::frame::FrameLayers::Checksum
        >;
    
    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Checksum<TMessage, TAllMessages>;
    
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile "howto6/frame/Frame.h"
template <
   typename TMessage,
   typename TAllMessages = howto6::input::AllMessages<TMessage>,
   typename TOpt = howto6::options::DefaultOptions
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
    ///     @li layer_chekcusmType() for @ref FrameLayers::ChekcusmType layer.
    ///     @li layer_id() for @ref FrameLayers::Id layer.
    ///     @li layer_size() for @ref FrameLayers::Size layer.
    ///     @li layer_sync() for @ref FrameLayers::Sync layer.
    ///     @li layer_checksum() for @ref FrameLayers::Checksum layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        chekcusmType,
        id,
        size,
        sync,
        checksum
    );
};

} // namespace frame

} // namespace howto6

