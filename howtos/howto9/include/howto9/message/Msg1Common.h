// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto9::message::Msg1 message and its fields.

#pragma once

#include <cstdint>

namespace howto9
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref howto9::message::Msg1 message.
/// @see howto9::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto9::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     howto9::message::Msg1Fields::F1 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref howto9::message::Msg1Fields::F1 field.
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
///     @ref howto9::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref howto9::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace howto9
