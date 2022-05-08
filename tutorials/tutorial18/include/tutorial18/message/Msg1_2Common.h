// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial18::message::Msg1_2 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial18
{

namespace message
{


/// @brief Common types and functions for fields of 
///     @ref tutorial18::message::Msg1_2 message.
/// @see tutorial18::message::Msg1_2Fields
struct Msg1_2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial18::message::Msg1_2Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial18::message::Msg1_2Fields::F1 field.
        using ValueType = std::uint32_t;
        
        /// @brief Name of the @ref tutorial18::message::Msg1_2Fields::F1 field.
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
///     @ref tutorial18::message::Msg1_2 message.
struct Msg1_2Common
{
    /// @brief Name of the @ref tutorial18::message::Msg1_2 message.
    static const char* name()
    {
        return "Message 1 (2)";
    }
    
};

} // namespace message

} // namespace tutorial18



