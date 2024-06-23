// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg7 message and its fields.

#pragma once

#include "tutorial2/field/D7_1Common.h"
#include "tutorial2/field/D7_2Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg7 message.
/// @see tutorial2::message::Msg7Fields
struct Msg7FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg7Fields::F1 field.
    struct F1Common : public tutorial2::field::D7_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg7Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg7Fields::F2 field.
    using F2MembersCommon = tutorial2::field::D7_2MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg7Fields::F2 field.
    struct F2Common : public tutorial2::field::D7_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg7Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg7Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg7Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg7 message.
struct Msg7Common
{
    /// @brief Name of the @ref tutorial2::message::Msg7 message.
    static const char* name()
    {
        return "Message 7";
    }
};

} // namespace message

} // namespace tutorial2
