// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/Bitfield.h"
#include "comms/field/BitmaskValue.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "tutorial17/field/FieldBase.h"
#include "tutorial17/field/MsgId.h"
#include "tutorial17/frame/FrameCommon.h"
#include "tutorial17/frame/layer/IdWithFlags.h"
#include "tutorial17/frame/layer/SizeWithFlags.h"
#include "tutorial17/input/AllMessages.h"
#include "tutorial17/options/DefaultOptions.h"

namespace tutorial17
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial17/frame/Frame.h
template <typename TOpt = tutorial17::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
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
                    tutorial17::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::FixedBitLength<12U>
                >
            {
                using Base =
                    comms::field::IntValue<
                        tutorial17::field::FieldBase<>,
                        std::uint16_t,
                        comms::option::def::FixedBitLength<12U>
                    >;
            public:
                /// @brief Re-definition of the value type.
                using ValueType = typename Base::ValueType;

                /// @brief Compile time detection of special values presence.
                static constexpr bool hasSpecials()
                {
                    return tutorial17::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::SizeCommon::hasSpecials();
                }

                /// @brief Name of the field.
                static const char* name()
                {
                    return tutorial17::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::SizeCommon::name();
                }
            };

            /// @brief Definition of <b>"Flags"</b> field.
            class Flags : public
                comms::field::BitmaskValue<
                    tutorial17::field::FieldBase<>,
                    comms::option::def::FixedBitLength<4U>,
                    comms::option::def::BitmaskReservedBits<0xEU, 0x0U>
                >
            {
                using Base =
                    comms::field::BitmaskValue<
                        tutorial17::field::FieldBase<>,
                        comms::option::def::FixedBitLength<4U>,
                        comms::option::def::BitmaskReservedBits<0xEU, 0x0U>
                    >;
            public:
                /// @brief Provides names and generates access functions for internal bits.
                /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
                ///     related to @b comms::field::BitmaskValue class from COMMS library
                ///     for details.
                ///
                ///      The generated enum values and functions are:
                ///      @li @b BitIdx_F1, @b getBitValue_F1() and @b setBitValue_F1().
                COMMS_BITMASK_BITS_SEQ(
                    F1
                );

                /// @brief Retrieve name of the bit.
                /// @see @ref tutorial17::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::bitName().
                static const char* bitName(BitIdx idx)
                {
                    return
                        tutorial17::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::bitName(
                            static_cast<std::size_t>(idx));
                }

                /// @brief Name of the field.
                static const char* name()
                {
                    return tutorial17::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::name();
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
                tutorial17::field::FieldBase<>,
                typename FieldMembers::All
            >
        {
            using Base =
                comms::field::Bitfield<
                    tutorial17::field::FieldBase<>,
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
            ///         for tutorial17::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Size member field.
            ///     @li @b FieldIdx_flags index, @b Field_flags type and @b field_flags() access function -
            ///         for tutorial17::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Flags member field.
            COMMS_FIELD_MEMBERS_NAMES(
                size,
                flags
            );

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial17::frame::FrameLayersCommon::SizeWithFlagsMembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "SizeWithFlags".
    using SizeWithFlags =
        tutorial17::frame::layer::SizeWithFlags<
            typename SizeWithFlagsMembers::Field,
            Data,
            typename TOpt::frame::FrameLayers::SizeWithFlags
        >;

    /// @brief Scope for field(s) of @ref IdWithFlags layer.
    struct IdWithFlagsMembers
    {
        /// @brief Scope for all the member fields of
        ///     @ref Field field.
        struct FieldMembers
        {
            /// @brief Definition of <b>"MsgId"</b> field.
            using MsgId =
                tutorial17::field::MsgId<
                    TOpt,
                    comms::option::def::FixedBitLength<6U>
                >;

            /// @brief Definition of <b>"Flags"</b> field.
            class Flags : public
                comms::field::BitmaskValue<
                    tutorial17::field::FieldBase<>,
                    comms::option::def::FixedBitLength<2U>,
                    comms::option::def::BitmaskReservedBits<0x2U, 0x0U>
                >
            {
                using Base =
                    comms::field::BitmaskValue<
                        tutorial17::field::FieldBase<>,
                        comms::option::def::FixedBitLength<2U>,
                        comms::option::def::BitmaskReservedBits<0x2U, 0x0U>
                    >;
            public:
                /// @brief Provides names and generates access functions for internal bits.
                /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
                ///     related to @b comms::field::BitmaskValue class from COMMS library
                ///     for details.
                ///
                ///      The generated enum values and functions are:
                ///      @li @b BitIdx_F1, @b getBitValue_F1() and @b setBitValue_F1().
                COMMS_BITMASK_BITS_SEQ(
                    F1
                );

                /// @brief Retrieve name of the bit.
                /// @see @ref tutorial17::frame::FrameLayersCommon::IdWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::bitName().
                static const char* bitName(BitIdx idx)
                {
                    return
                        tutorial17::frame::FrameLayersCommon::IdWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::bitName(
                            static_cast<std::size_t>(idx));
                }

                /// @brief Name of the field.
                static const char* name()
                {
                    return tutorial17::frame::FrameLayersCommon::IdWithFlagsMembersCommon::FieldMembersCommon::FlagsCommon::name();
                }
            };

            /// @brief All members bundled in @b std::tuple.
            using All =
                std::tuple<
                   MsgId,
                   Flags
                >;
        };

        /// @brief Definition of <b>"Field"</b> field.
        class Field : public
            comms::field::Bitfield<
                tutorial17::field::FieldBase<>,
                typename FieldMembers::All
            >
        {
            using Base =
                comms::field::Bitfield<
                    tutorial17::field::FieldBase<>,
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
            ///         for tutorial17::frame::FrameLayers::IdWithFlagsMembers::FieldMembers::MsgId member field.
            ///     @li @b FieldIdx_flags index, @b Field_flags type and @b field_flags() access function -
            ///         for tutorial17::frame::FrameLayers::IdWithFlagsMembers::FieldMembers::Flags member field.
            COMMS_FIELD_MEMBERS_NAMES(
                msgId,
                flags
            );

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial17::frame::FrameLayersCommon::IdWithFlagsMembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "IdWithFlags".
    template <typename TMessage, typename TAllMessages>
    using IdWithFlags =
        tutorial17::frame::layer::IdWithFlags<
            typename IdWithFlagsMembers::Field,
            TMessage,
            TAllMessages,
            SizeWithFlags,
            typename TOpt::frame::FrameLayers::IdWithFlags
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = IdWithFlags<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial17/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial17::input::AllMessages<TMessage>,
   typename TOpt = tutorial17::options::DefaultOptions
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
    ///     @li layer_sizeWithFlags() for @ref FrameLayers::SizeWithFlags layer.
    ///     @li layer_idWithFlags() for @ref FrameLayers::IdWithFlags layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        sizeWithFlags,
        idWithFlags
    );
};

} // namespace frame

} // namespace tutorial17
