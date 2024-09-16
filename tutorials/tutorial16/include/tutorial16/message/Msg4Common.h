// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial16::message::Msg4 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial16
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial16::message::Msg4 message.
/// @see tutorial16::message::Msg4Fields
struct Msg4FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial16::message::Msg4Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial16::message::Msg4Fields::F1 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref tutorial16::message::Msg4Fields::F1 field.
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
};

/// @brief Common types and functions of 
///     @ref tutorial16::message::Msg4 message.
struct Msg4Common
{
    /// @brief Name of the @ref tutorial16::message::Msg4 message.
    static const char* name()
    {
        return "Message 4";
    }
};

} // namespace message

} // namespace tutorial16
