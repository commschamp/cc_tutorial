// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg9 message and its fields.

#pragma once

#include "tutorial2/field/B9_1Common.h"
#include "tutorial2/field/B9_2Common.h"

namespace tutorial2
{

namespace message
{


/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg9 message.
/// @see tutorial2::message::Msg9Fields
struct Msg9FieldsCommon
{
    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg9Fields::F1 field.
    using F1MembersCommon = tutorial2::field::B9_1MembersCommon;
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg9Fields::F1 field.
    struct F1Common : public tutorial2::field::B9_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg9Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg9Fields::F2 field.
    using F2MembersCommon = tutorial2::field::B9_2MembersCommon;
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg9Fields::F2 field.
    struct F2Common : public tutorial2::field::B9_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg9Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
    };
    
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg9 message.
struct Msg9Common
{
    /// @brief Name of the @ref tutorial2::message::Msg9 message.
    static const char* name()
    {
        return "Message 9";
    }
    
};

} // namespace message

} // namespace tutorial2



