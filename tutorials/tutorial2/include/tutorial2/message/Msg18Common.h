// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg18 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg18 message.
/// @see tutorial2::message::Msg18Fields
struct Msg18FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg18Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg18Fields::F1Members::Length field.
        struct LengthCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg18Fields::F1Members::Length field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial2::message::Msg18Fields::F1Members::Length field.
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
    ///     @ref tutorial2::message::Msg18Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg18Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg18Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg18Fields::F2Members::ActF2 field.
        struct ActF2Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg18Fields::F2Members::ActF2 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial2::message::Msg18Fields::F2Members::ActF2 field.
            static const char* name()
            {
                return "ActF2";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg18Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg18Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg18Fields::F3 field.
    struct F3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg18Fields::F3Members::ActF3 field.
        struct ActF3Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg18Fields::F3Members::ActF3 field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial2::message::Msg18Fields::F3Members::ActF3 field.
            static const char* name()
            {
                return "ActF3";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg18Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg18Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg18 message.
struct Msg18Common
{
    /// @brief Name of the @ref tutorial2::message::Msg18 message.
    static const char* name()
    {
        return "Message 18";
    }
};

} // namespace message

} // namespace tutorial2
