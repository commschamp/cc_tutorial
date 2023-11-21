// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial14::message::Msg2 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial14
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial14::message::Msg2 message.
/// @see tutorial14::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial14::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial14::message::Msg2Fields::F1 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref tutorial14::message::Msg2Fields::F1 field.
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
///     @ref tutorial14::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref tutorial14::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace tutorial14
