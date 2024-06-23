// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto8::message::Msg1 message and its fields.

#pragma once

#include <cstdint>

namespace howto8
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto8::message::Msg1 message.
/// @see howto8::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto8::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     howto8::message::Msg1Fields::F1 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref howto8::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref howto8::message::Msg1Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto8::message::Msg1Fields::F2Members::F2Field field.
        struct F2FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto8::message::Msg1Fields::F2Members::F2Field field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref howto8::message::Msg1Fields::F2Members::F2Field field.
            static const char* name()
            {
                return "F2Field";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref howto8::message::Msg1Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref howto8::message::Msg1Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref howto8::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref howto8::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace howto8
