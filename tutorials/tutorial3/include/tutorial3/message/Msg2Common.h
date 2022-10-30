// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial3::message::Msg2 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial3
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial3::message::Msg2 message.
/// @see tutorial3::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial3::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial3::message::Msg2Fields::F1 field.
        using ValueType = std::uint32_t;

        /// @brief Name of the @ref tutorial3::message::Msg2Fields::F1 field.
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
    ///     @ref tutorial3::message::Msg2Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial3::message::Msg2Fields::F2 field.
        using ValueType = double;

        /// @brief Name of the @ref tutorial3::message::Msg2Fields::F2 field.
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
///     @ref tutorial3::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref tutorial3::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace tutorial3
