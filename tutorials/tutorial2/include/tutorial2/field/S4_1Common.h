// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::S4_1 field.

#pragma once

#include <type_traits>

namespace tutorial2
{

namespace field
{


/// @brief Common types and functions for
///     @ref tutorial2::field::S4_1 field.
struct S4_1Common
{
    /// @brief Name of the @ref tutorial2::field::S4_1 field.
    static const char* name()
    {
        return "S4_1";
    }
    
    /// @brief Retrieve name of the bit of
    ///     @ref tutorial2::field::S4_1 field.
    static const char* bitName(std::size_t idx)
    {
        static const char* Map[] = {
            "B0",
            "B1",
            "B2"
        };
        
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        if (MapSize <= idx) {
            return nullptr;
        }
        
        return Map[idx];
    }
    
    
};

} // namespace field

} // namespace tutorial2

