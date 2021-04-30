// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg14 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg14 message.
/// @see tutorial2::message::Msg14Fields
struct Msg14FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg14Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg14Fields::F1 field.
        using ValueType = std::int8_t;
    
        /// @brief Name of the @ref tutorial2::message::Msg14Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg14Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg14Fields::F2 field.
        using ValueType = std::int8_t;
    
        /// @brief Name of the @ref tutorial2::message::Msg14Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
    };
    
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg14Fields::F3 field.
    struct F3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg14Fields::F3Members::ActF3 field.
        struct ActF3Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg14Fields::F3Members::ActF3 field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial2::message::Msg14Fields::F3Members::ActF3 field.
            static const char* name()
            {
                return "ActF3";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial2::message::Msg14Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg14Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
        
    };
    
    
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg14 message.
/// @see tutorial2::message::Msg14
struct Msg14Common
{
    /// @brief Name of the @ref tutorial2::message::Msg14 message.
    static const char* name()
    {
        return "Message 14";
    }
    
};

} // namespace message

} // namespace tutorial2


