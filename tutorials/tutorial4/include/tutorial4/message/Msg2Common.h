// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial4::message::Msg2 message and its fields.

#pragma once

namespace tutorial4
{

namespace message
{


/// @brief Common types and functions for fields of 
///     @ref tutorial4::message::Msg2 message.
/// @see tutorial4::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial4::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial4::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial4::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref tutorial4::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
    
};

} // namespace message

} // namespace tutorial4



