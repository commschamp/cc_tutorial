// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial13::message::Msg1_3 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial13
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial13::message::Msg1_3 message.
/// @see tutorial13::message::Msg1_3Fields
struct Msg1_3FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial13::message::Msg1_3Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial13::message::Msg1_3Fields::F1 field.
        using ValueType = std::uint16_t;
    
        /// @brief Name of the @ref tutorial13::message::Msg1_3Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial13::message::Msg1_3 message.
/// @see tutorial13::message::Msg1_3
struct Msg1_3Common
{
    /// @brief Name of the @ref tutorial13::message::Msg1_3 message.
    static const char* name()
    {
        return "Message 1 (3)";
    }
    
};

} // namespace message

} // namespace tutorial13


