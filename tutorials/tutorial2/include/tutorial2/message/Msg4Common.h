// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg4 message and its fields.

#pragma once

#include "tutorial2/field/S4_1Common.h"
#include "tutorial2/field/S4_2Common.h"
#include "tutorial2/field/S4_3Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg4 message.
/// @see tutorial2::message::Msg4Fields
struct Msg4FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg4Fields::F1 field.
    struct F1Common : public tutorial2::field::S4_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg4Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg4Fields::F2 field.
    struct F2Common : public tutorial2::field::S4_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg4Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg4Fields::F3 field.
    struct F3Common : public tutorial2::field::S4_3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg4Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg4 message.
struct Msg4Common
{
    /// @brief Name of the @ref tutorial2::message::Msg4 message.
    static const char* name()
    {
        return "Message 4";
    }
};

} // namespace message

} // namespace tutorial2
