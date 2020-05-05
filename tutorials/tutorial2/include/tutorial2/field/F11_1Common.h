// Generated by commsdsl2comms v3.4.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::F11_1 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::F11_1 field.
struct F11_1Common
{
    /// @brief Re-definition of the value type used by
    ///     tutorial2::field::F11_1 field.
    using ValueType = std::uint8_t;

    /// @brief Name of the @ref tutorial2::field::F11_1 field.
    static const char* name()
    {
        return "Field 11_1";
    }
    
};

} // namespace field

} // namespace tutorial2


