// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial15::message::Msg1 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial15
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial15::message::Msg1 message.
/// @see tutorial15::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial15::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial15::message::Msg1Fields::F1 field.
        using ValueType = std::uint32_t;
    
        /// @brief Name of the @ref tutorial15::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial15::message::Msg1 message.
/// @see tutorial15::message::Msg1
struct Msg1Common
{
    /// @brief Name of the @ref tutorial15::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
    
};

} // namespace message

} // namespace tutorial15


