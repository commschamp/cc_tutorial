// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto6::field::ChecksumType field.

#pragma once

#include <cstdint>
#include <type_traits>

namespace howto6
{

namespace field
{

/// @brief Common types and functions for
///     @ref howto6::field::ChecksumType field.
struct ChecksumTypeCommon
{
    /// @brief Values enumerator for
    ///     @ref howto6::field::ChecksumType field.
    enum class ValueType : std::uint8_t
    {
        Sum8 = 0, ///< value @b Sum8.
        Crc16 = 1, ///< value @b Crc16.
        Crc32 = 2, ///< value @b Crc32.
        
        // --- Extra values generated for convenience ---
        FirstValue = 0, ///< First defined value.
        LastValue = 2, ///< Last defined value.
        ValuesLimit = 3, ///< Upper limit for defined values.
        
    };
    
    /// @brief Name of the @ref howto6::field::ChecksumType field.
    static const char* name()
    {
        return "ChecksumType";
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(ValueType val)
    {
        static const char* Map[] = {
            "Sum8",
            "Crc16",
            "Crc32"
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        
        if (MapSize <= static_cast<std::size_t>(val)) {
            return nullptr;
        }
        
        return Map[static_cast<std::size_t>(val)];
    }
    
};

/// @brief Values enumerator for
///     @ref howto6::field::ChecksumType field.
using ChecksumTypeVal = ChecksumTypeCommon::ValueType;

} // namespace field

} // namespace howto6

