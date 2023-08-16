// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto5::field::InterfaceFlags field.

#pragma once

#include <type_traits>

namespace howto5
{

namespace field
{

/// @brief Common types and functions for
///     @ref howto5::field::InterfaceFlags field.
struct InterfaceFlagsCommon
{
    /// @brief Name of the @ref howto5::field::InterfaceFlags field.
    static const char* name()
    {
        return "InterfaceFlags";
    }

    /// @brief Retrieve name of the bit of
    ///     @ref howto5::field::InterfaceFlags field.
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

} // namespace howto5
