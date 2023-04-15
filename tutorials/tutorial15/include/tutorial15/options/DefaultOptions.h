// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial15
{

namespace options
{

/// @brief Empty class to serve as the base for options.
struct EmptyOptions {};

/// @brief Default (empty) options of the protocol.
template <typename TBase = EmptyOptions>
struct DefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for @ref
        ///     tutorial15::message::Msg1 message.
        using Msg1 = comms::option::EmptyOption;

        /// @brief Extra options for fields of
        ///     @ref tutorial15::message::Msg2 message.
        struct Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial15::message::Msg2Fields::F1
            ///     field.
            using F1 = comms::option::EmptyOption;
        };

        /// @brief Extra options for fields of
        ///     @ref tutorial15::message::Msg3 message.
        struct Msg3Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial15::message::Msg3Fields::F1
            ///     field.
            using F1 = comms::option::EmptyOption;
        };
    }; // struct message

    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial15::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial15::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;

            /// @brief Extra options for @ref
            ///     tutorial15::frame::FrameLayers::Id
            ///     layer.
            using Id = comms::option::EmptyOption;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace tutorial15
