// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/Bitfield.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/TransportValueLayer.h"
#include "howto1/field/FieldBase.h"
#include "howto1/field/InterfaceFlags.h"
#include "howto1/field/MsgId.h"
#include "howto1/frame/FrameCommon.h"
#include "howto1/frame/layer/SizeWithFlags.h"
#include "howto1/input/AllMessages.h"
#include "howto1/options/DefaultOptions.h"

namespace howto1
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto1/frame/Frame.h
template <typename TOpt = howto1::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;

    /// @brief Definition of layer "Flags".
    using Flags =
        comms::protocol::TransportValueLayer<
            howto1::field::InterfaceFlags<
                TOpt,
                comms::option::def::EmptySerialization
            >,
            0U,
            Data,
            comms::option::def::PseudoValue
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            howto1::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Flags,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Scope for field(s) of @ref SizeWithFlags layer.
    struct SizeWithFlagsMembers
    {
        /// @brief Scope for all the member fields of
        ///     @ref Field field.
        struct FieldMembers
        {
            /// @brief Definition of <b>"Size"</b> field.
            class Size : public
                comms::field::IntValue<
                    howto1::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::FixedBitLength<12U>
                >
            {
                using Base =
                    comms::field::IntValue<
                        howto1::field::FieldBase<>,
                        std::uint16_t,
                        comms::option::def::FixedBitLength<12U>
                    >;
            public:
                /// @brief Re-definition of the value type.
                using ValueType = typename Base::ValueType;

                /// @brief Compile time detection of special values presence.
                static constexpr bool hasSpecials()
                {
                    return howto1::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::SizeCommon::hasSpecials();
                }

                /// @brief Name of the field.
                static const char* name()
                {
                    return howto1::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::SizeCommon::name();
                }
            };

            /// @brief Definition of <b>"Flags"</b> field.
            class Flags : public
                howto1::field::InterfaceFlags<
                    TOpt,
                    comms::option::def::FixedBitLength<4U>
                >
            {
                using Base =
                    howto1::field::InterfaceFlags<
                        TOpt,
                        comms::option::def::FixedBitLength<4U>
                    >;
            public:
                /// @brief Name of the field.
                static const char* name()
                {
                    return howto1::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::name();
                }
            };

            /// @brief All members bundled in @b std::tuple.
            using All =
                std::tuple<
                   Size,
                   Flags
                >;
        };

        /// @brief Definition of <b>"Field"</b> field.
        class Field : public
            comms::field::Bitfield<
                howto1::field::FieldBase<>,
                typename FieldMembers::All
            >
        {
            using Base =
                comms::field::Bitfield<
                    howto1::field::FieldBase<>,
                    typename FieldMembers::All
                >;
        public:
            /// @brief Allow access to internal fields.
            /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
            ///     related to @b comms::field::Bitfield class from COMMS library
            ///     for details.
            ///
            ///     The generated values, types and access functions are:
            ///     @li @b FieldIdx_size index, @b Field_size type and @b field_size() access function -
            ///         for howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Size member field.
            ///     @li @b FieldIdx_flags index, @b Field_flags type and @b field_flags() access function -
            ///         for howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Flags member field.
            COMMS_FIELD_MEMBERS_NAMES(
                size,
                flags
            );

            /// @brief Name of the field.
            static const char* name()
            {
                return howto1::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "SizeWithFlags".
    template <typename TMessage, typename TAllMessages>
    using SizeWithFlags =
        howto1::frame::layer::SizeWithFlags<
            typename SizeWithFlagsMembers::Field,
            Id<TMessage, TAllMessages>,
            typename TOpt::frame::FrameLayers::SizeWithFlags
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = SizeWithFlags<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile howto1/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto1::input::AllMessages<TMessage>,
   typename TOpt = howto1::options::DefaultOptions
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
    ///     @li layer_sizeWithFlags() for @ref FrameLayers::SizeWithFlags layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        flags,
        id,
        sizeWithFlags
    );
};

} // namespace frame

} // namespace howto1
