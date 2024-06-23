// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial23::message::Msg1 message and its fields.

#pragma once

#include "t23_ext/ns1/field/S1Common.h"
#include "tutorial23/field/I1Common.h"

namespace tutorial23
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial23::message::Msg1 message.
/// @see tutorial23::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial23::message::Msg1Fields::F1 field.
    struct F1Common : public tutorial23::field::I1Common
    {
        /// @brief Name of the @ref tutorial23::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common definitions of the member fields of
    ///     @ref tutorial23::message::Msg1Fields::F2 field.
    using F2MembersCommon = t23_ext::ns1::field::S1MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial23::message::Msg1Fields::F2 field.
    struct F2Common : public t23_ext::ns1::field::S1Common
    {
        /// @brief Name of the @ref tutorial23::message::Msg1Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial23::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref tutorial23::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace tutorial23
