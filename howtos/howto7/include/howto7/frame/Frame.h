// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "howto7/field/FieldBase.h"
#include "howto7/field/MsgId.h"
#include "howto7/frame/FrameCommon.h"
#include "howto7/frame/layer/AlternatingSync.h"
#include "howto7/input/AllMessages.h"
#include "howto7/options/DefaultOptions.h"

namespace howto7
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile howto7/frame/Frame.h
template <typename TOpt = howto7::options::DefaultOptions>
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
            howto7::field::MsgId<
                TOpt
            >,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::Id
        >;

    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"SizeField"</b> field.
        class SizeField : public
            comms::field::IntValue<
                howto7::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto7::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto7::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto7::frame::FrameLayersCommon::SizeMembersCommon::SizeFieldCommon::name();
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

    /// @brief Scope for field(s) of @ref AlternatingSync layer.
    struct AlternatingSyncMembers
    {
        /// @brief Definition of <b>"SyncField"</b> field.
        class SyncField : public
            comms::field::IntValue<
                howto7::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto7::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto7::frame::FrameLayersCommon::AlternatingSyncMembersCommon::SyncFieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto7::frame::FrameLayersCommon::AlternatingSyncMembersCommon::SyncFieldCommon::name();
            }
        };
    };

    /// @brief Definition of layer "AlternatingSync".
    template <typename TMessage, typename TAllMessages>
    using AlternatingSync =
        howto7::frame::layer::AlternatingSync<
            typename AlternatingSyncMembers::SyncField,
            Size<TMessage, TAllMessages>,
            typename TOpt::frame::FrameLayers::AlternatingSync
        >;

    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = AlternatingSync<TMessage, TAllMessages>;
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile howto7/frame/Frame.h
template <
   typename TMessage,
   typename TAllMessages = howto7::input::AllMessages<TMessage>,
   typename TOpt = howto7::options::DefaultOptions
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
    ///     @li @b Layer_alternatingSync type and @b layer_alternatingSync() function
    ///         for @ref FrameLayers::AlternatingSync layer.
    COMMS_PROTOCOL_LAYERS_NAMES(
        data,
        id,
        size,
        alternatingSync
    );
};

} // namespace frame

} // namespace howto7
