// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto6::message::Msg2 message and its fields.

#pragma once

#include <cstdint>

namespace howto6
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto6::message::Msg2 message.
/// @see howto6::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto6::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     howto6::message::Msg2Fields::F1 field.
        using ValueType = std::uint32_t;

        /// @brief Name of the @ref howto6::message::Msg2Fields::F1 field.
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
///     @ref howto6::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref howto6::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace howto6
