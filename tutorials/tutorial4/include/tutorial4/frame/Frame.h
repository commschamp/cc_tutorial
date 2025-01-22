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
#include "tutorial4/field/FieldBase.h"
#include "tutorial4/field/MsgId.h"
#include "tutorial4/frame/FrameCommon.h"
#include "tutorial4/input/AllMessages.h"
#include "tutorial4/options/DefaultOptions.h"

namespace tutorial4
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial4/frame/Frame.h
template <typename TOpt = tutorial4::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Scope for field(s) of @ref Data layer.
    struct DataMembers
    {
        /// @brief Custom field for @ref tutorial4::frame::FrameLayers::Data layer
        class Field : public
            comms::field::ArrayList<
                tutorial4::field::FieldBase<>,
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

    /// @brief Definition of layer "ID".
    template <typename TMessage, typename TAllMessages>
    using ID =
        comms::protocol::MsgIdLayer<
            tutorial4::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::ID
        >;

    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::HasName
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            typename SizeMembers::SizeField,
            ID<TMessage, TAllMessages>
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Size<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial4/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial4::input::AllMessages<TMessage>,
   typename TOpt = tutorial4::options::DefaultOptions
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
    ///     @li @b Layer_iD type and @b layer_iD() function
    ///         for @ref FrameLayers::ID layer.
    ///     @li @b Layer_size type and @b layer_size() function
    ///         for @ref FrameLayers::Size layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        iD,
        size
    );
};

} // namespace frame

} // namespace tutorial4
