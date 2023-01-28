// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto2::message::Msg1 message and its fields.

#pragma once

namespace howto2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto2::message::Msg1 message.
/// @see howto2::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto2::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref howto2::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };
};

/// @brief Common types and functions of 
///     @ref howto2::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref howto2::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace howto2
