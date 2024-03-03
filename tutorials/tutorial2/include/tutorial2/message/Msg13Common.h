// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg13 message and its fields.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg13 message.
/// @see tutorial2::message::Msg13Fields
struct Msg13FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg13Fields::Flags field.
    struct FlagsCommon
    {
        /// @brief Name of the @ref tutorial2::message::Msg13Fields::Flags field.
        static const char* name()
        {
            return "Flags";
        }

        /// @brief Retrieve name of the bit of
        ///     @ref tutorial2::message::Msg13Fields::Flags field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "F2Present",
                "F3Missing"
            };

            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }

            return Map[idx];
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg13Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg13Fields::F2Members::ActF2 field.
        struct ActF2Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg13Fields::F2Members::ActF2 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial2::message::Msg13Fields::F2Members::ActF2 field.
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
    ///     @ref tutorial2::message::Msg13Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg13Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg13Fields::F3 field.
    struct F3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg13Fields::F3Members::ActF3 field.
        struct ActF3Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg13Fields::F3Members::ActF3 field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial2::message::Msg13Fields::F3Members::ActF3 field.
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
    ///     @ref tutorial2::message::Msg13Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg13Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg13 message.
struct Msg13Common
{
    /// @brief Name of the @ref tutorial2::message::Msg13 message.
    static const char* name()
    {
        return "Message 13";
    }
};

} // namespace message

} // namespace tutorial2
