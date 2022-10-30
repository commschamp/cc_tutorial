// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial4
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
        struct KeyValuePropMembers
        {
            struct Prop3Members
            {
                /// @brief Extra options for @ref
                ///     tutorial4::field::KeyValuePropMembers::Prop3Members::Val
                ///     field.
                using Val = comms::option::EmptyOption;
            }; // struct Prop3Members
        }; // struct KeyValuePropMembers

        struct TlvPropMembers
        {
            struct Prop6Members
            {
                /// @brief Extra options for @ref
                ///     tutorial4::field::TlvPropMembers::Prop6Members::Val
                ///     field.
                using Val = comms::option::EmptyOption;
            }; // struct Prop6Members

            struct AnyMembers
            {
                /// @brief Extra options for @ref
                ///     tutorial4::field::TlvPropMembers::AnyMembers::Val
                ///     field.
                using Val = comms::option::EmptyOption;
            }; // struct AnyMembers
        }; // struct TlvPropMembers
    }; // struct field

    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for fields of
        ///     @ref tutorial4::message::Msg1 message.
        struct Msg1Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial4::message::Msg1Fields::F1
            ///     field.
            using F1 = comms::option::EmptyOption;
        };

        /// @brief Extra options for fields of
        ///     @ref tutorial4::message::Msg2 message.
        struct Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial4::message::Msg2Fields::F1
            ///     field.
            using F1 = comms::option::EmptyOption;
        };
    }; // struct message

    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial4::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial4::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;

            /// @brief Extra options for @ref
            ///     tutorial4::frame::FrameLayers::ID layer.
            using ID = comms::option::EmptyOption;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace tutorial4
