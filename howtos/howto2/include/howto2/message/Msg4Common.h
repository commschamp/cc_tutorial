// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto2::message::Msg4 message and its fields.

#pragma once

#include <cstdint>

namespace howto2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto2::message::Msg4 message.
/// @see howto2::message::Msg4Fields
struct Msg4FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto2::message::Msg4Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     howto2::message::Msg4Fields::F1 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref howto2::message::Msg4Fields::F1 field.
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

    /// @brief Common types and functions for
    ///     @ref howto2::message::Msg4Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     howto2::message::Msg4Fields::F2 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref howto2::message::Msg4Fields::F2 field.
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

/// @brief Common types and functions of 
///     @ref howto2::message::Msg4 message.
struct Msg4Common
{
    /// @brief Name of the @ref howto2::message::Msg4 message.
    static const char* name()
    {
        return "Message 4";
    }
};

} // namespace message

} // namespace howto2
