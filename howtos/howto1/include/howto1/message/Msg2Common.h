// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto1::message::Msg2 message and its fields.

#pragma once

#include <cstdint>

namespace howto1
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto1::message::Msg2 message.
/// @see howto1::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref howto1::message::Msg2Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto1::message::Msg2Fields::F1Members::Length field.
        struct LengthCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto1::message::Msg2Fields::F1Members::Length field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref howto1::message::Msg2Fields::F1Members::Length field.
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
    ///     @ref howto1::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref howto1::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref howto1::message::Msg2Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto1::message::Msg2Fields::F2Members::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto1::message::Msg2Fields::F2Members::Field field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref howto1::message::Msg2Fields::F2Members::Field field.
            static const char* name()
            {
                return "F2";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref howto1::message::Msg2Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref howto1::message::Msg2Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref howto1::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref howto1::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace howto1
