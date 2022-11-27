// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg10 message and its fields.

#pragma once

#include "tutorial2/field/L10_1Common.h"
#include "tutorial2/field/L10_2Common.h"
#include "tutorial2/field/L10_3Common.h"
#include "tutorial2/field/L10_4Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg10 message.
/// @see tutorial2::message::Msg10Fields
struct Msg10FieldsCommon
{
    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg10Fields::F1 field.
    using F1MembersCommon = tutorial2::field::L10_1MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg10Fields::F1 field.
    struct F1Common : public tutorial2::field::L10_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg10Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg10Fields::F2 field.
    using F2MembersCommon = tutorial2::field::L10_2MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg10Fields::F2 field.
    struct F2Common : public tutorial2::field::L10_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg10Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg10Fields::F3 field.
    using F3MembersCommon = tutorial2::field::L10_3MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg10Fields::F3 field.
    struct F3Common : public tutorial2::field::L10_3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg10Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };

    /// @brief Common definitions of the member fields of
    ///     @ref tutorial2::message::Msg10Fields::F4 field.
    using F4MembersCommon = tutorial2::field::L10_4MembersCommon;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg10Fields::F4 field.
    struct F4Common : public tutorial2::field::L10_4Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg10Fields::F4 field.
        static const char* name()
        {
            return "F4";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg10 message.
struct Msg10Common
{
    /// @brief Name of the @ref tutorial2::message::Msg10 message.
    static const char* name()
    {
        return "Message 10";
    }
};

} // namespace message

} // namespace tutorial2
