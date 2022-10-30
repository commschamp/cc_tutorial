// Generated by commsdsl2comms v5.1.2

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
#include "tutorial16/field/FieldBase.h"
#include "tutorial16/field/InterfaceFlags.h"
#include "tutorial16/field/MsgId.h"
#include "tutorial16/frame/FrameCommon.h"
#include "tutorial16/input/AllMessages.h"
#include "tutorial16/options/DefaultOptions.h"

namespace tutorial16
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial16/frame/Frame.h
template <typename TOpt = tutorial16::options::DefaultOptions>
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
            tutorial16::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Scope for field(s) of @ref Flags layer.
    struct FlagsMembers
    {
        /// @brief Definition of <b>"Field"</b> field.
        class Field : public
            tutorial16::field::InterfaceFlags<
                TOpt
            >
        {
            using Base =
                tutorial16::field::InterfaceFlags<
                    TOpt
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial16::frame::FrameLayersCommon::FlagsMembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Flags".
    template <typename TMessage, typename TAllMessages>
    using Flags =
        comms::protocol::TransportValueLayer<
            typename FlagsMembers::Field,
            0U,
            Id<TMessage, TAllMessages>
        >;

    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                tutorial16::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial16::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial16::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial16::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            typename SizeMembers::SizeField,
            Flags<TMessage, TAllMessages>
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Size<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial16/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial16::input::AllMessages<TMessage>,
   typename TOpt = tutorial16::options::DefaultOptions
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
    ///     @li layer_flags() for @ref FrameLayers::Flags layer.
    ///     @li layer_size() for @ref FrameLayers::Size layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        id,
        flags,
        size
    );
};

} // namespace frame

} // namespace tutorial16
