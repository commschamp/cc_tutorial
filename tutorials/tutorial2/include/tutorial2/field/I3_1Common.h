// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::I3_1 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::I3_1 field.
struct I3_1Common
{
    /// @brief Re-definition of the value type used by
    ///     tutorial2::field::I3_1 field.
    using ValueType = std::int32_t;

    /// @brief Name of the @ref tutorial2::field::I3_1 field.
    static const char* name()
    {
        return "I3_1";
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return false;
    }
};

} // namespace field

} // namespace tutorial2
