// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::B8_1 field.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::B8_1 field.
struct B8_1MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B8_1Members::M1 field.
    struct M1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::B8_1Members::M1 field.
        using ValueType = std::uint16_t;
    
        /// @brief Name of the @ref tutorial2::field::B8_1Members::M1 field.
        static const char* name()
        {
            return "M1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B8_1Members::M2 field.
    struct M2Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::field::B8_1Members::M2 field.
        enum class ValueType : std::uint8_t
        {
            V1 = 0, ///< value @b V1.
            V2 = 1, ///< value @b V2.
            
            // --- Extra values generated for convenience ---
            FirstValue = 0, ///< First defined value.
            LastValue = 1, ///< Last defined value.
            ValuesLimit = 2, ///< Upper limit for defined values.
            
        };
        
        /// @brief Name of the @ref tutorial2::field::B8_1Members::M2 field.
        static const char* name()
        {
            return "M2";
        }
        
        /// @brief Retrieve name of the enum value
        static const char* valueName(ValueType val)
        {
            static const char* Map[] = {
                "V1",
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
    ///     @ref tutorial2::field::B8_1Members::M2 field.
    using M2Val = M2Common::ValueType;
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial2::field::B8_1Members::M3 field.
    struct M3Common
    {
        /// @brief Name of the @ref tutorial2::field::B8_1Members::M3 field.
        static const char* name()
        {
            return "M3";
        }
        
    };
    
    
};

/// @brief Scope for all the common definitions of the
///     @ref tutorial2::field::B8_1 field.
struct B8_1Common
{
    /// @brief Name of the @ref tutorial2::field::B8_1 field.
    static const char* name()
    {
        return "B8_1";
    }
    
};


} // namespace field

} // namespace tutorial2


