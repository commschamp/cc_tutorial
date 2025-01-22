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
    /// @brief Scope for field(s) of @ref Data layer.
    struct DataMembers
    {
        /// @brief Custom field for @ref howto9::frame::FrameLayers::Data layer
        class Field : public
            comms::field::ArrayList<
                howto9::field::FieldBase<>,
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

    /// @brief Scope for field(s) of @ref Checksum layer.
    struct ChecksumMembers
    {
        /// @brief Definition of <b>"ChecksumField"</b> field.
        class ChecksumField : public
            comms::field::IntValue<
                howto9::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    howto9::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::HasName
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
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_NAMES macro
    ///     from COMMS library for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Layer_data type and @b layer_data() function
    ///         for @ref FrameLayers::Data layer.
    ///     @li @b Layer_checksum type and @b layer_checksum() function
    ///         for @ref FrameLayers::Checksum layer.
    ///     @li @b Layer_id type and @b layer_id() function
    ///         for @ref FrameLayers::Id layer.
    ///     @li @b Layer_size type and @b layer_size() function
    ///         for @ref FrameLayers::Size layer.
    ///     @li @b Layer_sync type and @b layer_sync() function
    ///         for @ref FrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        checksum,
        id,
        size,
        sync
    );
};

} // namespace frame

} // namespace howto9
