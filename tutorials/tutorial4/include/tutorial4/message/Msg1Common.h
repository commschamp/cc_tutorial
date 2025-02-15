// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial4::message::Msg1 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial4
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial4::message::Msg1 message.
/// @see tutorial4::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial4::message::Msg1Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial4::message::Msg1Fields::F1Members::Count field.
        struct CountCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial4::message::Msg1Fields::F1Members::Count field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial4::message::Msg1Fields::F1Members::Count field.
            static const char* name()
            {
                return "Count";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial4::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial4::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial4::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref tutorial4::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace tutorial4
