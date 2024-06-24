// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto10::message::Msg3 message and its fields.

#pragma once

#include <cstdint>

namespace howto10
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto10::message::Msg3 message.
/// @see howto10::message::Msg3Fields
struct Msg3FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref howto10::message::Msg3Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto10::message::Msg3Fields::F1Members::Length field.
        struct LengthCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto10::message::Msg3Fields::F1Members::Length field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref howto10::message::Msg3Fields::F1Members::Length field.
            static const char* name()
            {
                return "Length";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref howto10::message::Msg3Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref howto10::message::Msg3Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };
};

/// @brief Common types and functions of 
///     @ref howto10::message::Msg3 message.
struct Msg3Common
{
    /// @brief Name of the @ref howto10::message::Msg3 message.
    static const char* name()
    {
        return "Message 3";
    }
};

} // namespace message

} // namespace howto10
