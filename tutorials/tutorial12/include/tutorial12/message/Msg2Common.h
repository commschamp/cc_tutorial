// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial12::message::Msg2 message and its fields.

#pragma once

namespace tutorial12
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial12::message::Msg2 message.
/// @see tutorial12::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial12::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial12::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial12::message::Msg2Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial12::message::Msg2Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial12::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref tutorial12::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace tutorial12
