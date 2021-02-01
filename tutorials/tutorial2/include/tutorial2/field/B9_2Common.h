// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::B9_2 field.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::B9_2 field.
struct B9_2MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B9_2Members::M1 field.
    struct M1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::B9_2Members::M1 field.
        using ValueType = std::uint16_t;
    
        /// @brief Name of the @ref tutorial2::field::B9_2Members::M1 field.
        static const char* name()
        {
            return "M1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B9_2Members::M2 field.
    struct M2Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::field::B9_2Members::M2 field.
        enum class ValueType : std::uint8_t
        {
            V1 = 2, ///< value @b V1.
            V2 = 5, ///< value @b V2.
            
            // --- Extra values generated for convenience ---
            FirstValue = 2, ///< First defined value.
            LastValue = 5, ///< Last defined value.
            ValuesLimit = 6, ///< Upper limit for defined values.
            
        };
        
        /// @brief Name of the @ref tutorial2::field::B9_2Members::M2 field.
        static const char* name()
        {
            return "M2";
        }
        
        /// @brief Retrieve name of the enum value
        static const char* valueName(ValueType val)
        {
            static const char* Map[] = {
                nullptr,
                nullptr,
                "V1",
                nullptr,
                nullptr,
                "V2"
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            
            if (MapSize <= static_cast<std::size_t>(val)) {
                return nullptr;
            }
            
            return Map[static_cast<std::size_t>(val)];
        }
        
    };
    
    /// @brief Values enumerator for
    ///     @ref tutorial2::field::B9_2Members::M2 field.
    using M2Val = M2Common::ValueType;
    
    /// @brief Common functions for
    ///     @ref tutorial2::field::B9_2Members::M3 field.
    struct M3Common
    {
        /// @brief Name of the @ref tutorial2::field::B9_2Members::M3 field.
        static const char* name()
        {
            return "M3";
        }
        
        /// @brief Retrieve name of the bit of
        ///     @ref tutorial2::field::B9_2Members::M3 field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "B0",
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                "B5",
                nullptr,
                "B7"
            };
        
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }
        
            return Map[idx];
        }
        
    };
    
};

/// @brief Scope for all the common definitions of the
///     @ref tutorial2::field::B9_2 field.
struct B9_2Common
{
    /// @brief Name of the @ref tutorial2::field::B9_2 field.
    static const char* name()
    {
        return "B9_2";
    }
    
};


} // namespace field

} // namespace tutorial2


