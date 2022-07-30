// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial20::field::Version field.

#pragma once

#include <cstdint>

namespace tutorial20
{

namespace field
{


/// @brief Common types and functions for
///     @ref tutorial20::field::Version field.
struct VersionCommon
{
    /// @brief Re-definition of the value type used by
    ///     tutorial20::field::Version field.
    using ValueType = std::uint16_t;
    
    /// @brief Name of the @ref tutorial20::field::Version field.
    static const char* name()
    {
        return "Version";
    }
    
    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return false;
    }
    
    
};

} // namespace field

} // namespace tutorial20

