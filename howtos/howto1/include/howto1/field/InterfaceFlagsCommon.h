// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto1::field::InterfaceFlags field.

#pragma once

#include <type_traits>

namespace howto1
{

namespace field
{

/// @brief Common types and functions for
///     @ref howto1::field::InterfaceFlags field.
struct InterfaceFlagsCommon
{
    /// @brief Name of the @ref howto1::field::InterfaceFlags field.
    static const char* name()
    {
        return "InterfaceFlags";
    }

    /// @brief Retrieve name of the bit of
    ///     @ref howto1::field::InterfaceFlags field.
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

} // namespace howto1
