// Generated by commsdsl2comms v3.3.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::E2_1 field.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::E2_1 field.
struct E2_1Common
{
    /// @brief Values enumerator for
    ///     @ref tutorial2::field::E2_1 field.
    enum class ValueType : std::uint8_t
    {
        V1 = 0, ///< Some value
        V2 = 1, ///< value @b V2
        V3 = 2, ///< value @b V3
        
        // --- Extra values generated for convenience ---
        FirstValue = 0, ///< First defined value.
        LastValue = 2, ///< Last defined value.
        ValuesLimit = 3, ///< Upper limit for defined values.
        
    };
    
    /// @brief Name of the @ref tutorial2::field::E2_1 field.
    static const char* name()
    {
        return "E2_1";
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(ValueType val)
    {
        static const char* Map[] = {
            "V1",
            "V2",
            "V3"
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        
        if (MapSize <= static_cast<std::size_t>(val)) {
            return nullptr;
        }
        
        return Map[static_cast<std::size_t>(val)];
    }
    
};

/// @brief Values enumerator for
///     @ref tutorial2::field::E2_1 field.
using E2_1Val = E2_1Common::ValueType;

} // namespace field

} // namespace tutorial2

