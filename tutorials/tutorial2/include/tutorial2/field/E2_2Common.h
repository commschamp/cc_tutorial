// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::E2_2 field.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace tutorial2
{

namespace field
{


/// @brief Common types and functions for
///     @ref tutorial2::field::E2_2 field.
struct E2_2Common
{
    /// @brief Values enumerator for
    ///     @ref tutorial2::field::E2_2 field.
    enum class ValueType : std::uint16_t
    {
        V1 = 0, ///< value @b V1. 
        V2 = 100, ///< value @b V2. 
        V3 = 271, ///< value @b V3. 
        
        // --- Extra values generated for convenience ---
        FirstValue = 0, ///< First defined value.
        LastValue = 271, ///< Last defined value.
        ValuesLimit = 272, ///< Upper limit for defined values.
    };
    
    /// @brief Single value name info entry
    using ValueNameInfo = std::pair<ValueType, const char*>;
    
    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @details The @b first value of the pair is pointer to the map array,
    ///     The @b second value of the pair is the size of the array.
    using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;
    
    /// @brief Name of the @ref tutorial2::field::E2_2 field.
    static const char* name()
    {
        return "E2_2";
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(ValueType val)
    {
        auto namesMapInfo = valueNamesMap();
        auto begIter = namesMapInfo.first;
        auto endIter = begIter + namesMapInfo.second;
        auto iter = std::lower_bound(
            begIter, endIter, val,
            [](const ValueNameInfo& info, ValueType v) -> bool
            {
                return info.first < v;
            });
        
        if ((iter == endIter) || (iter->first != val)) {
            return nullptr;
        }
        
        return iter->second;
    }
    
    /// @brief Retrieve map of enum value names
    static ValueNamesMapInfo valueNamesMap()
    {
        static const ValueNameInfo Map[] = {
            std::make_pair(ValueType::V1, "V1"),
            std::make_pair(ValueType::V2, "V2"),
            std::make_pair(ValueType::V3, "V3")
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        
        return std::make_pair(&Map[0], MapSize);
    }
    
    
};

/// @brief Values enumerator for
///     @ref tutorial2::field::E2_2 field.
using E2_2Val = E2_2Common::ValueType;


} // namespace field

} // namespace tutorial2

