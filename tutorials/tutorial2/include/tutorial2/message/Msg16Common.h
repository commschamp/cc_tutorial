// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg16 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg16 message.
/// @see tutorial2::message::Msg16Fields
struct Msg16FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg16Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg16Fields::F1 field.
        using ValueType = std::uint8_t;

        /// @brief Name of the @ref tutorial2::message::Msg16Fields::F1 field.
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
    ///     @ref tutorial2::message::Msg16Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg16Fields::F2 field.
        using ValueType = std::int8_t;

        /// @brief Name of the @ref tutorial2::message::Msg16Fields::F2 field.
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

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg16Fields::F3 field.
    struct F3Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg16Fields::F3 field.
        using ValueType = std::int8_t;

        /// @brief Name of the @ref tutorial2::message::Msg16Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg16 message.
struct Msg16Common
{
    /// @brief Name of the @ref tutorial2::message::Msg16 message.
    static const char* name()
    {
        return "Message 16";
    }
};

} // namespace message

} // namespace tutorial2
