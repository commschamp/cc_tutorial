// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::S6_2 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::S6_2 field.
struct S6_2MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::S6_2Members::Length field.
    struct LengthCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::S6_2Members::Length field.
        using ValueType = std::uint8_t;

        /// @brief Name of the @ref tutorial2::field::S6_2Members::Length field.
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
///     @ref tutorial2::field::S6_2 field.
struct S6_2Common
{
    /// @brief Name of the @ref tutorial2::field::S6_2 field.
    static const char* name()
    {
        return "S6_2";
    }
};

} // namespace field

} // namespace tutorial2
