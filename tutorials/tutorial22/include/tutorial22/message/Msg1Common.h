// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial22::message::Msg1 message and its fields.

#pragma once

namespace tutorial22
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial22::message::Msg1 message.
/// @see tutorial22::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial22::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial22::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial22::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref tutorial22::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace tutorial22
