// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/Bitfield.h"
#include "comms/field/BitmaskValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "howto8/field/FieldBase.h"
#include "howto8/field/Flags.h"
#include "howto8/field/MsgId.h"
#include "howto8/frame/FrameCommon.h"
#include "howto8/frame/layer/Flags.h"
#include "howto8/frame/layer/Id.h"
#include "howto8/input/AllMessages.h"
#include "howto8/options/DefaultOptions.h"

namespace howto8
{

namespace frame
{


/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto8/frame/Frame.h
template <typename TOpt = howto8::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;
    
    /// @brief Scope for field(s) of @ref Flags layer.
    struct FlagsMembers
    {
        /// @brief Definition of <b>"OptFlags"</b> field.
        class OptFlags : public
            comms::field::Optional<
                howto8::field::Flags<TOpt>,
                comms::option::def::MissingByDefault
            >
        {
            using Base =
                comms::field::Optional<
                    howto8::field::Flags<TOpt>,
                    comms::option::def::MissingByDefault
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return howto8::frame::FrameLayersCommon::FlagsMembersCommon::OptFlagsCommon::name();
            }
            
        
        };
        
        
    };
    
    /// @brief Definition of layer "Flags".
    using Flags =
        howto8::frame::layer::Flags<
            typename FlagsMembers::OptFlags,
            Data,
            typename TOpt::frame::FrameLayers::Flags
        >;
    
    /// @brief Scope for field(s) of @ref Id layer.
    struct IdMembers
    {
        /// @brief Scope for all the member fields of
        ///     @ref Field field.
        struct FieldMembers
        {
            /// @brief Definition of <b>"MsgId"</b> field.
            using MsgId =
                howto8::field::MsgId<
                    TOpt,
                    comms::option::def::FixedBitLength<7U>
                >;
            
            
            /// @brief Definition of <b>"Ctrl"</b> field.
            class Ctrl : public
                comms::field::BitmaskValue<
                    howto8::field::FieldBase<>,
                    comms::option::def::FixedBitLength<1U>
                >
            {
                using Base =
                    comms::field::BitmaskValue<
                        howto8::field::FieldBase<>,
                        comms::option::def::FixedBitLength<1U>
                    >;
            public:
                /// @brief Provides names and generates access functions for internal bits.
                /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
                ///     related to @b comms::field::BitmaskValue class from COMMS library
                ///     for details.
                ///
                ///      The generated enum values and functions are:
                ///      @li @b BitIdx_HasFlags, @b getBitValue_HasFlags() and @b setBitValue_HasFlags().
                COMMS_BITMASK_BITS_SEQ(
                    HasFlags
                );
                
                /// @brief Retrieve name of the bit.
                /// @see @ref howto8::frame::FrameLayersCommon::IdMembersCommon::FieldMembersCommon::CtrlCommon::bitName().
                static const char* bitName(BitIdx idx)
                {
                    return
                        howto8::frame::FrameLayersCommon::IdMembersCommon::FieldMembersCommon::CtrlCommon::bitName(
                            static_cast<std::size_t>(idx));
                }
                
                /// @brief Name of the field.
                static const char* name()
                {
                    return howto8::frame::FrameLayersCommon::IdMembersCommon::FieldMembersCommon::CtrlCommon::name();
                }
                
            
            };
            
            
            /// @brief All members bundled in @b std::tuple.
            using All =
                std::tuple<
                   MsgId,
                   Ctrl
                >;
        };
        
        /// @brief Definition of <b>"Field"</b> field.
        class Field : public
            comms::field::Bitfield<
                howto8::field::FieldBase<>,
                typename FieldMembers::All
            >
        {
            using Base =
                comms::field::Bitfield<
                    howto8::field::FieldBase<>,
                    typename FieldMembers::All
                >;
        public:
            /// @brief Allow access to internal fields.
            /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
            ///     related to @b comms::field::Bitfield class from COMMS library
            ///     for details.
            ///
            ///     The generated values, types and access functions are:
            ///     @li @b FieldIdx_msgId index, @b Field_msgId type and @b field_msgId() access function -
            ///         for howto8::frame::FrameLayers::IdMembers::FieldMembers::MsgId member field.
            ///     @li @b FieldIdx_ctrl index, @b Field_ctrl type and @b field_ctrl() access function -
            ///         for howto8::frame::FrameLayers::IdMembers::FieldMembers::Ctrl member field.
            COMMS_FIELD_MEMBERS_NAMES(
                msgId,
                ctrl
            );
            
            /// @brief Name of the field.
            static const char* name()
            {
                return howto8::frame::FrameLayersCommon::IdMembersCommon::FieldCommon::name();
            }
            
        
        };
        
        
    };
    
    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        howto8::frame::layer::Id<
            typename IdMembers::Field,
            TMessage,
            TAllMessages,
            Flags,
            typename TOpt::frame::FrameLayers::Id
        >;
    
    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                howto8::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto8::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;
            
            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto8::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }
            
            
            /// @brief Name of the field.
            static const char* name()
            {
                return howto8::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
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

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile howto8/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto8::input::AllMessages<TMessage>,
   typename TOpt = howto8::options::DefaultOptions
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
    ///     @li layer_flags() for @ref FrameLayers::Flags layer.
    ///     @li layer_id() for @ref FrameLayers::Id layer.
    ///     @li layer_size() for @ref FrameLayers::Size layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        flags,
        id,
        size
    );
};

} // namespace frame

} // namespace howto8


