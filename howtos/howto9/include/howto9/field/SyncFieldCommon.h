// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto9::field::SyncField field.

#pragma once

#include <cstdint>

namespace howto9
{

namespace field
{

/// @brief Common types and functions for
///     @ref howto9::field::SyncField field.
struct SyncFieldCommon
{
    /// @brief Re-definition of the value type used by
    ///     howto9::field::SyncField field.
    using ValueType = std::uint16_t;

    /// @brief Name of the @ref howto9::field::SyncField field.
    static const char* name()
    {
        return "SyncField";
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return false;
    }
};

} // namespace field

} // namespace howto9
