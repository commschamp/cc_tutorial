// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::I3_5 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::I3_5 field.
struct I3_5Common
{
    /// @brief Re-definition of the value type used by
    ///     tutorial2::field::I3_5 field.
    using ValueType = std::int16_t;

    /// @brief Name of the @ref tutorial2::field::I3_5 field.
    static const char* name()
    {
        return "I3_5";
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return false;
    }
};

} // namespace field

} // namespace tutorial2
