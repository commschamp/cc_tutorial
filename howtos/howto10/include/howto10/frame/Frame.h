// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/ChecksumLayer.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "comms/protocol/SyncPrefixLayer.h"
#include "comms/protocol/TransportValueLayer.h"
#include "comms/protocol/checksum/Crc.h"
#include "howto10/field/FieldBase.h"
#include "howto10/field/Flags.h"
#include "howto10/field/MsgId.h"
#include "howto10/frame/FrameCommon.h"
#include "howto10/frame/layer/Flags.h"
#include "howto10/input/AllMessages.h"
#include "howto10/options/DefaultOptions.h"

namespace howto10
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto10/frame/Frame.h
template <typename TOpt = howto10::options::DefaultOptions>
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
                howto10::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto10::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto10::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto10::frame::FrameLayersCommon::ChecksumMembersCommon::ChecksumFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "Checksum".
    using Checksum =
        comms::protocol::ChecksumLayer<
            typename ChecksumMembers::ChecksumField,
            comms::protocol::checksum::Crc_CCITT,
            Data,
            comms::option::def::ChecksumLayerVerifyBeforeRead
        >;

    /// @brief Definition of layer "PseudoFlags".
    using PseudoFlags =
        comms::protocol::TransportValueLayer<
            howto10::field::Flags<
                TOpt,
                comms::option::def::EmptySerialization
            >,
            0U,
            Checksum,
            comms::option::def::PseudoValue
        >;

    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            howto10::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            PseudoFlags,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Definition of layer "Flags".
    template <typename TMessage, typename TAllMessages>
    using Flags =
        howto10::frame::layer::Flags<
            howto10::field::Flags<
                TOpt
            >,
            Id<TMessage, TAllMessages>,
            typename TOpt::frame::FrameLayers::Flags
        >;

    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                howto10::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto10::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto10::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto10::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
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

    /// @brief Scope for field(s) of @ref Sync layer.
    struct SyncMembers
    {
        /// @brief Definition of <b>"SyncField"</b> field.
        class SyncField : public
            comms::field::IntValue<
                howto10::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                comms::option::def::DefaultNumValue<43981L>
            >
        {
            using Base =
                comms::field::IntValue<
                    howto10::field::FieldBase<>,
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
                return howto10::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto10::frame::FrameLayersCommon::SyncMembersCommon::SyncFieldCommon::name();
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
/// @headerfile howto10/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto10::input::AllMessages<TMessage>,
   typename TOpt = howto10::options::DefaultOptions
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
    ///     @li @b Layer_pseudoFlags type and @b layer_pseudoFlags() function
    ///         for @ref FrameLayers::PseudoFlags layer.
    ///     @li @b Layer_id type and @b layer_id() function
    ///         for @ref FrameLayers::Id layer.
    ///     @li @b Layer_flags type and @b layer_flags() function
    ///         for @ref FrameLayers::Flags layer.
    ///     @li @b Layer_size type and @b layer_size() function
    ///         for @ref FrameLayers::Size layer.
    ///     @li @b Layer_sync type and @b layer_sync() function
    ///         for @ref FrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        checksum,
        pseudoFlags,
        id,
        flags,
        size,
        sync
    );
};

} // namespace frame

} // namespace howto10
