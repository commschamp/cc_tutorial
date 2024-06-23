// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto2::message::Msg3 message and its fields.

#pragma once

namespace howto2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto2::message::Msg3 message.
/// @see howto2::message::Msg3Fields
struct Msg3FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto2::message::Msg3Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref howto2::message::Msg3Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };
};

/// @brief Common types and functions of 
///     @ref howto2::message::Msg3 message.
struct Msg3Common
{
    /// @brief Name of the @ref howto2::message::Msg3 message.
    static const char* name()
    {
        return "Message 3";
    }
};

} // namespace message

} // namespace howto2
