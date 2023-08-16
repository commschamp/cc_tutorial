// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::L10_2 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::L10_2 field.
struct L10_2MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_2Members::Element field.
    struct ElementCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::L10_2Members::Element field.
        using ValueType = std::int16_t;

        /// @brief Name of the @ref tutorial2::field::L10_2Members::Element field.
        static const char* name()
        {
            return "Element";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_2Members::Size field.
    struct SizeCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::L10_2Members::Size field.
        using ValueType = std::uint32_t;

        /// @brief Name of the @ref tutorial2::field::L10_2Members::Size field.
        static const char* name()
        {
            return "Size";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial2::field::L10_2 field.
struct L10_2Common
{
    /// @brief Name of the @ref tutorial2::field::L10_2 field.
    static const char* name()
    {
        return "L10_2";
    }
};

} // namespace field

} // namespace tutorial2
