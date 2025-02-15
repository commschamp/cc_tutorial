// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial20::message::Msg3 message and its fields.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial20
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial20::message::Msg3 message.
/// @see tutorial20::message::Msg3Fields
struct Msg3FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial20::message::Msg3Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial20::message::Msg3Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }

        /// @brief Retrieve name of the bit of
        ///     @ref tutorial20::message::Msg3Fields::F1 field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "B0",
                "B1"
            };

            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }

            return Map[idx];
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial20::message::Msg3Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial20::message::Msg3Fields::F2Members::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial20::message::Msg3Fields::F2Members::Field field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial20::message::Msg3Fields::F2Members::Field field.
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
    ///     @ref tutorial20::message::Msg3Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial20::message::Msg3Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial20::message::Msg3Fields::F3 field.
    struct F3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial20::message::Msg3Fields::F3Members::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial20::message::Msg3Fields::F3Members::Field field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial20::message::Msg3Fields::F3Members::Field field.
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

    /// @brief Common types and functions for
    ///     @ref tutorial20::message::Msg3Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial20::message::Msg3Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial20::message::Msg3Fields::F4 field.
    struct F4Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial20::message::Msg3Fields::F4 field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref tutorial20::message::Msg3Fields::F4 field.
        static const char* name()
        {
            return "F4";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial20::message::Msg3 message.
struct Msg3Common
{
    /// @brief Name of the @ref tutorial20::message::Msg3 message.
    static const char* name()
    {
        return "Message 3";
    }
};

} // namespace message

} // namespace tutorial20
