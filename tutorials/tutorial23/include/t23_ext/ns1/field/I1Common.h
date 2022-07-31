// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref t23_ext::ns1::field::I1 field.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace t23_ext
{

namespace ns1
{

namespace field
{


/// @brief Common types and functions for
///     @ref t23_ext::ns1::field::I1 field.
struct I1Common
{
    /// @brief Re-definition of the value type used by
    ///     t23_ext::ns1::field::I1 field.
    using ValueType = std::uint16_t;
    
    /// @brief Single special value name info entry.
    using SpecialNameInfo = std::pair<ValueType, const char*>;
    
    /// @brief Type returned from @ref specialNamesMap() member function.
    /// @details The @b first value of the pair is pointer to the map array,
    ///     The @b second value of the pair is the size of the array.
    using SpecialNamesMapInfo = std::pair<const SpecialNameInfo*, std::size_t>;
    
    /// @brief Name of the @ref t23_ext::ns1::field::I1 field.
    static const char* name()
    {
        return "I1";
    }
    
    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return true;
    }
    
    /// @brief Special value <b>"S1"</b>.
    static constexpr ValueType valueS1()
    {
        return static_cast<ValueType>(255);
    }
    
    
    /// @brief Retrieve map of special value names
    static SpecialNamesMapInfo specialNamesMap()
    {
        static const SpecialNameInfo Map[] = {
            std::make_pair(valueS1(), "S1")
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    
        return std::make_pair(&Map[0], MapSize);
    }
    
    
};

} // namespace field

} // namespace ns1

} // namespace t23_ext

