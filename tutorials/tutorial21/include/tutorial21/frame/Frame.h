// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "comms/protocol/TransportValueLayer.h"
#include "tutorial21/field/BasicFlags.h"
#include "tutorial21/field/FieldBase.h"
#include "tutorial21/field/MsgId.h"
#include "tutorial21/frame/FrameCommon.h"
#include "tutorial21/input/AllMessages.h"
#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial21/frame/Frame.h
template <typename TOpt = tutorial21::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Scope for field(s) of @ref Data layer.
    struct DataMembers
    {
        /// @brief Custom field for @ref tutorial21::frame::FrameLayers::Data layer
        class Field : public
            comms::field::ArrayList<
                tutorial21::field::FieldBase<>,
                std::uint8_t,
                typename TOpt::frame::FrameLayers::DataMembers::Field,
                comms::option::def::HasName
            >
        {
        public:
            static const char* name()
            {
                return "Data";
            }
        };
    };

    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            comms::option::def::FieldType<typename DataMembers::Field>
        >;

    /// @brief Definition of layer "Flags".
    using Flags =
        comms::protocol::TransportValueLayer<
            tutorial21::field::BasicFlags<
                TOpt
            >,
            0U,
            Data
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            tutorial21::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Flags,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"Size"</b> field.
        class Field : public
            comms::field::IntValue<
                tutorial21::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial21::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::HasName
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial21::frame::FrameLayersCommon::SizeMembersCommon::FieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial21::frame::FrameLayersCommon::SizeMembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            typename SizeMembers::Field,
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
/// @headerfile tutorial21/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial21::input::AllMessages<TMessage>,
   typename TOpt = tutorial21::options::DefaultOptions
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
    ///     @li @b Layer_flags type and @b layer_flags() function
    ///         for @ref FrameLayers::Flags layer.
    ///     @li @b Layer_id type and @b layer_id() function
    ///         for @ref FrameLayers::Id layer.
    ///     @li @b Layer_size type and @b layer_size() function
    ///         for @ref FrameLayers::Size layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        flags,
        id,
        size
    );
};

} // namespace frame

} // namespace tutorial21