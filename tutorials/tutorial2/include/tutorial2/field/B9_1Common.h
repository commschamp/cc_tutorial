// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::B9_1 field.

#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>

namespace tutorial2
{

namespace field
{


/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::B9_1 field.
struct B9_1MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B9_1Members::M1 field.
    struct M1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::B9_1Members::M1 field.
        using ValueType = std::uint8_t;
        
        /// @brief Name of the @ref tutorial2::field::B9_1Members::M1 field.
        static const char* name()
        {
            return "M1";
        }
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
        
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B9_1Members::M2 field.
    struct M2Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::field::B9_1Members::M2 field.
        enum class ValueType : std::uint8_t
        {
            V1 = 0, ///< value @b V1. 
            V2 = 1, ///< value @b V2. 
            
            // --- Extra values generated for convenience ---
            FirstValue = 0, ///< First defined value.
            LastValue = 1, ///< Last defined value.
            ValuesLimit = 2, ///< Upper limit for defined values.
        };
        
        /// @brief Single value name info entry
        using ValueNameInfo = const char*;
        
        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;
        
        /// @brief Name of the @ref tutorial2::field::B9_1Members::M2 field.
        static const char* name()
        {
            return "M2";
        }
        
        /// @brief Retrieve name of the enum value
        static const char* valueName(ValueType val)
        {
            auto namesMapInfo = valueNamesMap();
            if (namesMapInfo.second <= static_cast<std::size_t>(val)) {
                return nullptr;
            }
            
            return namesMapInfo.first[static_cast<std::size_t>(val)];
        }
        
        /// @brief Retrieve map of enum value names
        static ValueNamesMapInfo valueNamesMap()
        {
            static const char* Map[] = {
                "V1",
                "V2"
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            
            return std::make_pair(&Map[0], MapSize);
        }
        
        
    };
    
    /// @brief Values enumerator for
    ///     @ref tutorial2::field::B9_1Members::M2 field.
    using M2Val = M2Common::ValueType;
    
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B9_1Members::M3 field.
    struct M3Common
    {
        /// @brief Name of the @ref tutorial2::field::B9_1Members::M3 field.
        static const char* name()
        {
            return "M3";
        }
        
        /// @brief Retrieve name of the bit of
        ///     @ref tutorial2::field::B9_1Members::M3 field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "B0",
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                "B5"
            };
            
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }
            
            return Map[idx];
        }
        
        
    };
    
};

/// @brief Common types and functions for
///     @ref tutorial2::field::B9_1 field.
struct B9_1Common
{
    /// @brief Name of the @ref tutorial2::field::B9_1 field.
    static const char* name()
    {
        return "B9_1";
    }
    
};

} // namespace field

} // namespace tutorial2

