// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/ChecksumLayer.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "comms/protocol/SyncPrefixLayer.h"
#include "tutorial14/field/FieldBase.h"
#include "tutorial14/field/MsgId.h"
#include "tutorial14/frame/FrameCommon.h"
#include "tutorial14/frame/checksum/PlusOneSum.h"
#include "tutorial14/input/AllMessages.h"
#include "tutorial14/options/DefaultOptions.h"

namespace tutorial14
{

namespace frame
{


/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial14/frame/Frame.h
template <typename TOpt = tutorial14::options::DefaultOptions>
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
            tutorial14::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::Id
        >;
    
    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                tutorial14::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::NumValueSerOffset<2>
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial14::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::NumValueSerOffset<2>
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;
            
            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial14::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }
            
            
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial14::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
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
    
    /// @brief Scope for field(s) of @ref Checksum layer.
    struct ChecksumMembers
    {
        /// @brief Definition of <b>"ChecksumField"</b> field.
        class ChecksumField : public
            comms::field::IntValue<
                tutorial14::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial14::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;
            
            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial14::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::hasSpecials();
            }
            
            
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial14::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::name();
            }
            
        
        };
        
        
    };
    
    /// @brief Definition of layer "Checksum".
    template <typename TMessage, typename TAllMessages>
    using Checksum =
        comms::protocol::ChecksumLayer<
            typename ChecksumMembers::ChecksumField,
            tutorial14::frame::checksum::PlusOneSum,
            Size<TMessage, TAllMessages>
        >;
    
    /// @brief Scope for field(s) of @ref Sync layer.
    struct SyncMembers
    {
        /// @brief Definition of <b>"SyncField"</b> field.
        class SyncField : public
            comms::field::IntValue<
                tutorial14::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                comms::option::def::DefaultNumValue<43981L>
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial14::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                    comms::option::def::DefaultNumValue<43981L>
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;
            
            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial14::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::hasSpecials();
            }
            
            
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial14::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::name();
            }
            
        
        };
        
        
    };
    
    /// @brief Definition of layer "Sync".
    template <typename TMessage, typename TAllMessages>
    using Sync =
        comms::protocol::SyncPrefixLayer<
            typename SyncMembers::SyncField,
            Checksum<TMessage, TAllMessages>
        >;
    
    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Sync<TMessage, TAllMessages>;
    
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial14/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial14::input::AllMessages<TMessage>,
   typename TOpt = tutorial14::options::DefaultOptions
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
    ///     The generated functions are:
    ///     @li layer_data() for @ref FrameLayers::Data layer.
    ///     @li layer_id() for @ref FrameLayers::Id layer.
    ///     @li layer_size() for @ref FrameLayers::Size layer.
    ///     @li layer_checksum() for @ref FrameLayers::Checksum layer.
    ///     @li layer_sync() for @ref FrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        id,
        size,
        checksum,
        sync
    );
};

} // namespace frame

} // namespace tutorial14


