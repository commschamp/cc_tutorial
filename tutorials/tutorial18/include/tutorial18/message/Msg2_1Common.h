// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial18::message::Msg2_1 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial18
{

namespace message
{


/// @brief Common types and functions for fields of 
///     @ref tutorial18::message::Msg2_1 message.
/// @see tutorial18::message::Msg2_1Fields
struct Msg2_1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial18::message::Msg2_1Fields::Type field.
    struct TypeCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial18::message::Msg2_1Fields::Type field.
        using ValueType = std::uint8_t;
        
        /// @brief Name of the @ref tutorial18::message::Msg2_1Fields::Type field.
        static const char* name()
        {
            return "Type";
        }
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
        
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial18::message::Msg2_1Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial18::message::Msg2_1Fields::F1 field.
        using ValueType = std::uint16_t;
        
        /// @brief Name of the @ref tutorial18::message::Msg2_1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
        
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial18::message::Msg2_1 message.
struct Msg2_1Common
{
    /// @brief Name of the @ref tutorial18::message::Msg2_1 message.
    static const char* name()
    {
        return "Message 2 (1)";
    }
    
};

} // namespace message

} // namespace tutorial18



