// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial16::message::Msg2 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial16
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial16::message::Msg2 message.
/// @see tutorial16::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial16::message::Msg2Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial16::message::Msg2Fields::F1Members::Length field.
        struct LengthCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial16::message::Msg2Fields::F1Members::Length field.
            using ValueType = std::uint8_t;
        
            /// @brief Name of the @ref tutorial16::message::Msg2Fields::F1Members::Length field.
            static const char* name()
            {
                return "Length";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial16::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial16::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial16::message::Msg2Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial16::message::Msg2Fields::F2Members::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial16::message::Msg2Fields::F2Members::Field field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial16::message::Msg2Fields::F2Members::Field field.
            static const char* name()
            {
                return "F2";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial16::message::Msg2Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial16::message::Msg2Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
    };
    
    
};

/// @brief Common types and functions of 
///     @ref tutorial16::message::Msg2 message.
/// @see tutorial16::message::Msg2
struct Msg2Common
{
    /// @brief Name of the @ref tutorial16::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
    
};

} // namespace message

} // namespace tutorial16


