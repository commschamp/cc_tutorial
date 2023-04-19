// Generated by commsdsl2comms v6.1.0

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
#include "tutorial23/field/FieldBase.h"
#include "tutorial23/field/Length.h"
#include "tutorial23/field/MsgId.h"
#include "tutorial23/frame/FrameCommon.h"
#include "tutorial23/input/AllMessages.h"
#include "tutorial23/options/DefaultOptions.h"

namespace tutorial23
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile tutorial23/frame/Frame.h
template <typename TOpt = tutorial23::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::tutorial23::frame::FrameLayers::Data
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            tutorial23::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::tutorial23::frame::FrameLayers::Id
        >;

    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            tutorial23::field::Length<
                TOpt
            >,
            Id<TMessage, TAllMessages>
        >;

    /// @brief Scope for field(s) of @ref Sync layer.
    struct SyncMembers
    {
        /// @brief Definition of <b>"SyncField"</b> field.
        class SyncField : public
            comms::field::IntValue<
                tutorial23::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                comms::option::def::DefaultNumValue<43996L>
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial23::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                    comms::option::def::DefaultNumValue<43996L>
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial23::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial23::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::name();
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

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Sync<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial23/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial23::input::AllMessages<TMessage>,
   typename TOpt = tutorial23::options::DefaultOptions
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
    ///     @li @b Layer_id type and @b layer_id() function
    ///         for @ref FrameLayers::Id layer.
    ///     @li @b Layer_size type and @b layer_size() function
    ///         for @ref FrameLayers::Size layer.
    ///     @li @b Layer_sync type and @b layer_sync() function
    ///         for @ref FrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        id,
        size,
        sync
    );
};

} // namespace frame

} // namespace tutorial23
