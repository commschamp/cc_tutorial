// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg11 message and its fields.

#pragma once

#include "tutorial2/field/F11_1Common.h"
#include "tutorial2/field/F11_2Common.h"
#include "tutorial2/field/F11_3Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg11 message.
/// @see tutorial2::message::Msg11Fields
struct Msg11FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg11Fields::F11_1 field.
    using F11_1Common = tutorial2::field::F11_1Common;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg11Fields::F2 field.
    using F2Common = tutorial2::field::F11_2Common;

    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg11Fields::F3 field.
    using F3MembersCommon = tutorial2::field::F11_3MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg11Fields::F3 field.
    struct F3Common : public tutorial2::field::F11_3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg11Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg11 message.
struct Msg11Common
{
    /// @brief Name of the @ref tutorial2::message::Msg11 message.
    static const char* name()
    {
        return "Message 11";
    }
};

} // namespace message

} // namespace tutorial2
