// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::F5_1 field.

#pragma once

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::F5_1 field.
struct F5_1Common
{
    /// @brief Re-definition of the value type used by
    ///     tutorial2::field::F5_1 field.
    using ValueType = float;

    /// @brief Name of the @ref tutorial2::field::F5_1 field.
    static const char* name()
    {
        return "F5_1";
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return false;
    }
};

} // namespace field

} // namespace tutorial2
