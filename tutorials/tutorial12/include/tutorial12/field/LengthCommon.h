// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial12::field::Length field.

#pragma once

#include <cstdint>

namespace tutorial12
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial12::field::Length field.
struct LengthCommon
{
    /// @brief Re-definition of the value type used by
    ///     tutorial12::field::Length field.
    using ValueType = std::uint8_t;

    /// @brief Name of the @ref tutorial12::field::Length field.
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

} // namespace field

} // namespace tutorial12
