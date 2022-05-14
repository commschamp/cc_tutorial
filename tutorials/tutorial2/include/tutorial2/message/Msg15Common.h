// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg15 message and its fields.

#pragma once

#include <cstdint>
#include "tutorial2/field/I1Common.h"

namespace tutorial2
{

namespace message
{


/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg15 message.
/// @see tutorial2::message::Msg15Fields
struct Msg15FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg15Fields::F1 field.
    struct F1Common : public tutorial2::field::I1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg15Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg15Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg15Fields::F2 field.
        using ValueType = std::int16_t;
        
        /// @brief Name of the @ref tutorial2::message::Msg15Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
        
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg15Fields::F3 field.
    struct F3Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg15Fields::F3 field.
        using ValueType = std::int8_t;
        
        /// @brief Name of the @ref tutorial2::message::Msg15Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
        
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg15 message.
struct Msg15Common
{
    /// @brief Name of the @ref tutorial2::message::Msg15 message.
    static const char* name()
    {
        return "Message 15";
    }
    
};

} // namespace message

} // namespace tutorial2



