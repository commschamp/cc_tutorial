// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial23
{

namespace options
{

/// @brief Empty class to serve as the base for options.
struct EmptyOptions {};

/// @brief Default (empty) options of the protocol.
template <typename TBase = EmptyOptions>
struct DefaultOptionsT : public TBase
{
    struct tutorial23
    {
        /// @brief Extra options for messages.
        struct message
        {
            /// @brief Extra options for fields of
            ///     @ref tutorial23::message::Msg1 message.
            struct Msg1Fields
            {
                /// @brief Extra options for @ref
                ///     tutorial23::message::Msg1Fields::F2
                ///     field.
                using F2 = comms::option::EmptyOption;
            };
        }; // struct message

        /// @brief Extra options for frames.
        struct frame
        {
            /// @brief Extra options for layers of
            ///     @ref tutorial23::frame::Frame frame.
            struct FrameLayers
            {
                /// @brief Extra options for @ref
                ///     tutorial23::frame::FrameLayers::Data
                ///     layer.
                using Data = comms::option::EmptyOption;

                /// @brief Extra options for @ref
                ///     tutorial23::frame::FrameLayers::Id
                ///     layer.
                using Id = comms::option::EmptyOption;
            }; // struct FrameLayers
        }; // struct frame
    }; // struct tutorial23
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace tutorial23
