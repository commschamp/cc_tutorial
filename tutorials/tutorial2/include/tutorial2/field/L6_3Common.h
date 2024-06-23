// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::L6_3 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::L6_3 field.
struct L6_3Common
{
    /// @brief Re-definition of the value type used by
    ///     tutorial2::field::L6_3 field.
    using ValueType = std::uint16_t;

    /// @brief Name of the @ref tutorial2::field::L6_3 field.
    static const char* name()
    {
        return "L6_3";
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return false;
    }
};

} // namespace field

} // namespace tutorial2
