// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::I3_4 field.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace tutorial2
{

namespace field
{

/// @brief Common types and functions for
///     @ref tutorial2::field::I3_4 field.
struct I3_4Common
{
    /// @brief Re-definition of the value type used by
    ///     tutorial2::field::I3_4 field.
    using ValueType = std::uint8_t;

    /// @brief Single special value name info entry.
    using SpecialNameInfo = std::pair<ValueType, const char*>;

    /// @brief Type returned from @ref specialNamesMap() member function.
    /// @details The @b first value of the pair is pointer to the map array,
    ///     The @b second value of the pair is the size of the array.
    using SpecialNamesMapInfo = std::pair<const SpecialNameInfo*, std::size_t>;

    /// @brief Name of the @ref tutorial2::field::I3_4 field.
    static const char* name()
    {
        return "I3_4";
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return true;
    }

    /// @brief Special value <b>"S1"</b>.
    static constexpr ValueType valueS1()
    {
        return static_cast<ValueType>(1);
    }

    /// @brief Special value <b>"S2"</b>.
    static constexpr ValueType valueS2()
    {
        return static_cast<ValueType>(5);
    }

    /// @brief Retrieve map of special value names
    static SpecialNamesMapInfo specialNamesMap()
    {
        static const SpecialNameInfo Map[] = {
            std::make_pair(valueS1(), "S1"),
            std::make_pair(valueS2(), "S2")
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;

        return std::make_pair(&Map[0], MapSize);
    }
};

} // namespace field

} // namespace tutorial2
