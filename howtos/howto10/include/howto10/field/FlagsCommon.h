// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto10::field::Flags field.

#pragma once

#include <type_traits>

namespace howto10
{

namespace field
{

/// @brief Common types and functions for
///     @ref howto10::field::Flags field.
struct FlagsCommon
{
    /// @brief Name of the @ref howto10::field::Flags field.
    static const char* name()
    {
        return "Flags";
    }

    /// @brief Retrieve name of the bit of
    ///     @ref howto10::field::Flags field.
    static const char* bitName(std::size_t idx)
    {
        static const char* Map[] = {
            "B0",
            "B1"
        };

        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        if (MapSize <= idx) {
            return nullptr;
        }

        return Map[idx];
    }
};

} // namespace field

} // namespace howto10
