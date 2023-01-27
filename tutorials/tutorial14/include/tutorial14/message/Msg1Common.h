// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial14::message::Msg1 message and its fields.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial14
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial14::message::Msg1 message.
/// @see tutorial14::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial14::message::Msg1Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial14::message::Msg1Fields::F1Members::F1 field.
        struct F1Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial14::message::Msg1Fields::F1Members::F1 field.
            using ValueType = std::uint32_t;

            /// @brief Name of the @ref tutorial14::message::Msg1Fields::F1Members::F1 field.
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

    /// @brief Common types and functions for
    ///     @ref tutorial14::message::Msg1Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial14::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial14::message::Msg1Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial14::message::Msg1Fields::F2Members::F2 field.
        struct F2Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial14::message::Msg1Fields::F2Members::F2 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial14::message::Msg1Fields::F2Members::F2 field.
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
    ///     @ref tutorial14::message::Msg1Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial14::message::Msg1Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial14::message::Msg1Fields::F3 field.
    struct F3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial14::message::Msg1Fields::F3Members::F3 field.
        struct F3Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial14::message::Msg1Fields::F3Members::F3 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial14::message::Msg1Fields::F3Members::F3 field.
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
    ///     @ref tutorial14::message::Msg1Fields::F3 field.
    struct F3Common
    {
        /// @brief Name of the @ref tutorial14::message::Msg1Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial14::message::Msg1Fields::Flags field.
    struct FlagsCommon
    {
        /// @brief Name of the @ref tutorial14::message::Msg1Fields::Flags field.
        static const char* name()
        {
            return "Flags";
        }

        /// @brief Retrieve name of the bit of
        ///     @ref tutorial14::message::Msg1Fields::Flags field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "F2F3"
            };

            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }

            return Map[idx];
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial14::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref tutorial14::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace tutorial14
