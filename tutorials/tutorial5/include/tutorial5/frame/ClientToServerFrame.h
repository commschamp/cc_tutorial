// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of <b>"ClientToServerFrame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/ChecksumLayer.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "comms/protocol/SyncPrefixLayer.h"
#include "comms/protocol/checksum/Crc.h"
#include "tutorial5/field/FieldBase.h"
#include "tutorial5/field/MsgId.h"
#include "tutorial5/frame/ClientToServerFrameCommon.h"
#include "tutorial5/input/AllMessages.h"
#include "tutorial5/options/DefaultOptions.h"

namespace tutorial5
{

namespace frame
{

/// @brief Layers definition of @ref ClientToServerFrame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref ClientToServerFrame
/// @headerfile tutorial5/frame/ClientToServerFrame.h
template <typename TOpt = tutorial5::options::DefaultOptions>
struct ClientToServerFrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::ClientToServerFrameLayers::Data
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            tutorial5::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::ClientToServerFrameLayers::Id
        >;

    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                tutorial5::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::NumValueSerOffset<2>
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial5::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::NumValueSerOffset<2>
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial5::frame::ClientToServerFrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial5::frame::ClientToServerFrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
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

    /// @brief Scope for field(s) of @ref Checksum layer.
    struct ChecksumMembers
    {
        /// @brief Definition of <b>"ChecksumField"</b> field.
        class ChecksumField : public
            comms::field::IntValue<
                tutorial5::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial5::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial5::frame::ClientToServerFrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial5::frame::ClientToServerFrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Checksum".
    template <typename TMessage, typename TAllMessages>
    using Checksum =
        comms::protocol::ChecksumLayer<
            typename ChecksumMembers::ChecksumField,
            comms::protocol::checksum::Crc_CCITT,
            Size<TMessage, TAllMessages>
        >;

    /// @brief Scope for field(s) of @ref Sync layer.
    struct SyncMembers
    {
        /// @brief Definition of <b>"SyncField"</b> field.
        class SyncField : public
            comms::field::IntValue<
                tutorial5::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                comms::option::def::DefaultNumValue<43981L>
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial5::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                    comms::option::def::DefaultNumValue<43981L>
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial5::frame::ClientToServerFrameLayersCommon::SyncMembersCommon::SyncFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial5::frame::ClientToServerFrameLayersCommon::SyncMembersCommon::SyncFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Sync".
    template <typename TMessage, typename TAllMessages>
    using Sync =
        comms::protocol::SyncPrefixLayer<
            typename SyncMembers::SyncField,
            Checksum<TMessage, TAllMessages>
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Sync<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"ClientToServerFrame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile tutorial5/frame/ClientToServerFrame.h
template <
   typename TMessage,
   typename TAllMessages = tutorial5::input::AllMessages<TMessage>,
   typename TOpt = tutorial5::options::DefaultOptions
>
class ClientToServerFrame : public
    ClientToServerFrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base = typename
        ClientToServerFrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    /// @brief Allow access to frame definition layers.
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_NAMES macro
    ///     from COMMS library for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Layer_data type and @b layer_data() function
    ///         for @ref ClientToServerFrameLayers::Data layer.
    ///     @li @b Layer_id type and @b layer_id() function
    ///         for @ref ClientToServerFrameLayers::Id layer.
    ///     @li @b Layer_size type and @b layer_size() function
    ///         for @ref ClientToServerFrameLayers::Size layer.
    ///     @li @b Layer_checksum type and @b layer_checksum() function
    ///         for @ref ClientToServerFrameLayers::Checksum layer.
    ///     @li @b Layer_sync type and @b layer_sync() function
    ///         for @ref ClientToServerFrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        id,
        size,
        checksum,
        sync
    );
};

} // namespace frame

} // namespace tutorial5
