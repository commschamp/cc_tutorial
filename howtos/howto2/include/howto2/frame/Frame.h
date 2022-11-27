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
#include "howto2/field/FieldBase.h"
#include "howto2/field/MsgId.h"
#include "howto2/frame/FrameCommon.h"
#include "howto2/frame/layer/IdWithSize.h"
#include "howto2/input/AllMessages.h"
#include "howto2/options/DefaultOptions.h"

namespace howto2
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto2/frame/Frame.h
template <typename TOpt = howto2::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;

    /// @brief Scope for field(s) of @ref IdWithSize layer.
    struct IdWithSizeMembers
    {
        /// @brief Scope for all the member fields of
        ///     @ref Field field.
        struct FieldMembers
        {
            /// @brief Definition of <b>"Size"</b> field.
            class Size : public
                comms::field::IntValue<
                    howto2::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::FixedBitLength<12U>
                >
            {
                using Base =
                    comms::field::IntValue<
                        howto2::field::FieldBase<>,
                        std::uint16_t,
                        comms::option::def::FixedBitLength<12U>
                    >;
            public:
                /// @brief Re-definition of the value type.
                using ValueType = typename Base::ValueType;

                /// @brief Compile time detection of special values presence.
                static constexpr bool hasSpecials()
                {
                    return howto2::frame::FrameLayersCommon::IdWithSizeMembersCommon::FieldMembersCommon::SizeCommon::hasSpecials();
                }

                /// @brief Name of the field.
                static const char* name()
                {
                    return howto2::frame::FrameLayersCommon::IdWithSizeMembersCommon::FieldMembersCommon::SizeCommon::name();
                }
            };

            /// @brief Definition of <b>"MsgId"</b> field.
            using MsgId =
                howto2::field::MsgId<
                    TOpt,
                    comms::option::def::FixedBitLength<4U>
                >;

            /// @brief All members bundled in @b std::tuple.
            using All =
                std::tuple<
                   Size,
                   MsgId
                >;
        };

        /// @brief Definition of <b>"Field"</b> field.
        class Field : public
            comms::field::Bitfield<
                howto2::field::FieldBase<>,
                typename FieldMembers::All
            >
        {
            using Base =
                comms::field::Bitfield<
                    howto2::field::FieldBase<>,
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
            ///         for howto2::frame::FrameLayers::IdWithSizeMembers::FieldMembers::Size member field.
            ///     @li @b FieldIdx_msgId index, @b Field_msgId type and @b field_msgId() access function -
            ///         for howto2::frame::FrameLayers::IdWithSizeMembers::FieldMembers::MsgId member field.
            COMMS_FIELD_MEMBERS_NAMES(
                size,
                msgId
            );

            /// @brief Name of the field.
            static const char* name()
            {
                return howto2::frame::FrameLayersCommon::IdWithSizeMembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "IdWithSize".
    template <typename TMessage, typename TAllMessages>
    using IdWithSize =
        howto2::frame::layer::IdWithSize<
            typename IdWithSizeMembers::Field,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::IdWithSize
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = IdWithSize<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile howto2/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto2::input::AllMessages<TMessage>,
   typename TOpt = howto2::options::DefaultOptions
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
    ///     @li layer_idWithSize() for @ref FrameLayers::IdWithSize layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        idWithSize
    );
};

} // namespace frame

} // namespace howto2
