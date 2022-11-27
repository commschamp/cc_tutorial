// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::L10_3 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::L10_3 field.
struct L10_3MembersCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::field::L10_3Members::Element field.
    struct ElementMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::field::L10_3Members::ElementMembers::M1 field.
        struct M1Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::field::L10_3Members::ElementMembers::M1 field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial2::field::L10_3Members::ElementMembers::M1 field.
            static const char* name()
            {
                return "M1";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };

        /// @brief Common types and functions for
        ///     @ref tutorial2::field::L10_3Members::ElementMembers::M2 field.
        struct M2Common
        {
            /// @brief Name of the @ref tutorial2::field::L10_3Members::ElementMembers::M2 field.
            static const char* name()
            {
                return "M2";
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_3Members::Element field.
    struct ElementCommon
    {
        /// @brief Name of the @ref tutorial2::field::L10_3Members::Element field.
        static const char* name()
        {
            return "Element";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_3Members::Length field.
    struct LengthCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::L10_3Members::Length field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref tutorial2::field::L10_3Members::Length field.
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
///     @ref tutorial2::field::L10_3 field.
struct L10_3Common
{
    /// @brief Name of the @ref tutorial2::field::L10_3 field.
    static const char* name()
    {
        return "L10_3";
    }
};

} // namespace field

} // namespace tutorial2
