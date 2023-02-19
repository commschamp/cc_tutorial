// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg5 message and its fields.

#pragma once

#include "tutorial2/field/F5_1Common.h"
#include "tutorial2/field/F5_2Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg5 message.
/// @see tutorial2::message::Msg5Fields
struct Msg5FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg5Fields::F1 field.
    struct F1Common : public tutorial2::field::F5_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg5Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg5Fields::F2 field.
    struct F2Common : public tutorial2::field::F5_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg5Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg5 message.
struct Msg5Common
{
    /// @brief Name of the @ref tutorial2::message::Msg5 message.
    static const char* name()
    {
        return "Message 5";
    }
};

} // namespace message

} // namespace tutorial2
