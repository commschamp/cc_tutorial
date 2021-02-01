// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial17::message::Msg1 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial17
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial17::message::Msg1 message.
/// @see tutorial17::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial17::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial17::message::Msg1Fields::F1 field.
        using ValueType = std::uint16_t;
    
        /// @brief Name of the @ref tutorial17::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial17::message::Msg1Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial17::message::Msg1Fields::F2 field.
        using ValueType = std::uint16_t;
    
        /// @brief Name of the @ref tutorial17::message::Msg1Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
    };
    
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial17::message::Msg1Fields::F3 field.
    struct F3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial17::message::Msg1Fields::F3Members::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial17::message::Msg1Fields::F3Members::Field field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial17::message::Msg1Fields::F3Members::Field field.
            static const char* name()
            {
                return "F3";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial17::message::Msg1Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial17::message::Msg1Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
        
    };
    
    
};

/// @brief Common types and functions of 
///     @ref tutorial17::message::Msg1 message.
/// @see tutorial17::message::Msg1
struct Msg1Common
{
    /// @brief Name of the @ref tutorial17::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
    
};

} // namespace message

} // namespace tutorial17


