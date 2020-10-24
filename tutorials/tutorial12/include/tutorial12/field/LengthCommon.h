// Generated by commsdsl2comms v3.5.3

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
    
};

} // namespace field

} // namespace tutorial12


