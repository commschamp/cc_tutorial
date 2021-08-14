// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg6 message and its fields.

#pragma once

#include "tutorial2/field/S6_1Common.h"
#include "tutorial2/field/S6_2Common.h"
#include "tutorial2/field/S6_3Common.h"
#include "tutorial2/field/S6_4Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg6 message.
/// @see tutorial2::message::Msg6Fields
struct Msg6FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg6Fields::F1 field.
    struct F1Common : public tutorial2::field::S6_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg6Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg6Fields::F2 field.
    struct F2Common : public tutorial2::field::S6_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg6Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg6Fields::F3 field.
    struct F3Common : public tutorial2::field::S6_3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg6Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg6Fields::F4 field.
    struct F4Common : public tutorial2::field::S6_4Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg6Fields::F4 field.
        static const char* name()
        {
            return "F4";
        }
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial2::message::Msg6Fields::F5 field.
    struct F5Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg6Fields::F5 field.
        static const char* name()
        {
            return "F5";
        }
        
    };
    
    
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg6 message.
/// @see tutorial2::message::Msg6
struct Msg6Common
{
    /// @brief Name of the @ref tutorial2::message::Msg6 message.
    static const char* name()
    {
        return "Message 6";
    }
    
};

} // namespace message

} // namespace tutorial2


