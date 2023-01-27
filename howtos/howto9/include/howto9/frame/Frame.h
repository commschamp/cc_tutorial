// Generated by commsdsl2comms v5.2.0

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
#include "howto9/field/FieldBase.h"
#include "howto9/field/MsgId.h"
#include "howto9/field/SizeField.h"
#include "howto9/field/SyncField.h"
#include "howto9/frame/FrameCommon.h"
#include "howto9/frame/layer/Checksum.h"
#include "howto9/input/AllMessages.h"
#include "howto9/options/DefaultOptions.h"

namespace howto9
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto9/frame/Frame.h
template <typename TOpt = howto9::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;

    /// @brief Scope for field(s) of @ref Checksum layer.
    struct ChecksumMembers
    {
        /// @brief Definition of <b>"ChecksumField"</b> field.
        class ChecksumField : public
            comms::field::IntValue<
                howto9::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto9::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto9::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto9::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Checksum".
    using Checksum =
        howto9::frame::layer::Checksum<
            typename ChecksumMembers::ChecksumField,
            Data,
            typename TOpt::frame::FrameLayers::Checksum
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            howto9::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Checksum,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            howto9::field::SizeField<
                TOpt
            >,
            Id<TMessage, TAllMessages>
        >;

    /// @brief Definition of layer "Sync".
    template <typename TMessage, typename TAllMessages>
    using Sync =
        comms::protocol::SyncPrefixLayer<
            howto9::field::SyncField<
                TOpt,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>
            >,
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
/// @headerfile howto9/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto9::input::AllMessages<TMessage>,
   typename TOpt = howto9::options::DefaultOptions
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
    ///     @li layer_checksum() for @ref FrameLayers::Checksum layer.
    ///     @li layer_id() for @ref FrameLayers::Id layer.
    ///     @li layer_size() for @ref FrameLayers::Size layer.
    ///     @li layer_sync() for @ref FrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        checksum,
        id,
        size,
        sync
    );
};

} // namespace frame

} // namespace howto9
