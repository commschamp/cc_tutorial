// Generated by commsdsl2comms v3.5.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial18::message::Msg2_3 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial18
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial18::message::Msg2_3 message.
/// @see tutorial18::message::Msg2_3Fields
struct Msg2_3FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial18::message::Msg2_3Fields::Type field.
    struct TypeCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial18::message::Msg2_3Fields::Type field.
        using ValueType = std::uint8_t;
    
        /// @brief Name of the @ref tutorial18::message::Msg2_3Fields::Type field.
        static const char* name()
        {
            return "Type";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial18::message::Msg2_3Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial18::message::Msg2_3Fields::F1 field.
        using ValueType = std::uint64_t;
    
        /// @brief Name of the @ref tutorial18::message::Msg2_3Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial18::message::Msg2_3 message.
/// @see tutorial18::message::Msg2_3
struct Msg2_3Common
{
    /// @brief Name of the @ref tutorial18::message::Msg2_3 message.
    static const char* name()
    {
        return "Message 2 (3)";
    }
    
};

} // namespace message

} // namespace tutorial18


