// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial22
{

namespace options
{

/// @brief Empty class to serve as the base for options.
struct EmptyOptions {};

/// @brief Default (empty) options of the protocol.
template <typename TBase = EmptyOptions>
struct DefaultOptionsT : public TBase
{
    /// @brief Extra options for fields.
    struct field
    {
        struct TlvPropMembers
        {
            struct Prop2Members
            {
                /// @brief Extra options for @ref
                ///     tutorial22::field::TlvPropMembers::Prop2Members::Val
                ///     field.
                using Val = comms::option::EmptyOption;
            }; // struct Prop2Members

            struct AnyMembers
            {
                /// @brief Extra options for @ref
                ///     tutorial22::field::TlvPropMembers::AnyMembers::Val
                ///     field.
                using Val = comms::option::EmptyOption;
            }; // struct AnyMembers
        }; // struct TlvPropMembers
    }; // struct field

    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for fields of
        ///     @ref tutorial22::message::Msg1 message.
        struct Msg1Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial22::message::Msg1Fields::F1
            ///     field.
            using F1 = comms::option::EmptyOption;
        };
    }; // struct message

    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial22::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial22::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;

            /// @brief Extra options for @ref
            ///     tutorial22::frame::FrameLayers::Id
            ///     layer.
            using Id = comms::option::EmptyOption;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace tutorial22
