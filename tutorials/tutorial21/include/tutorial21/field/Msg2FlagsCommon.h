// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial21::field::Msg2Flags field.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace tutorial21
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial21::field::Msg2Flags field.
struct Msg2FlagsMembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial21::field::Msg2FlagsMembers::EnumMem field.
    struct EnumMemCommon
    {
        /// @brief Values enumerator for
        ///     @ref tutorial21::field::Msg2FlagsMembers::EnumMem field.
        enum class ValueType : std::uint8_t
        {
            V0 = 0, ///< value @b V0. 
            V1 = 1, ///< value @b V1. 
            V2 = 2, ///< value @b V2. 
            V3 = 3, ///< value @b V3. 

            // --- Extra values generated for convenience ---
            FirstValue = 0, ///< First defined value.
            LastValue = 3, ///< Last defined value.
            ValuesLimit = 4, ///< Upper limit for defined values.
        };

        /// @brief Single value name info entry
        using ValueNameInfo = const char*;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial21::field::Msg2FlagsMembers::EnumMem field.
        static const char* name()
        {
            return "EnumMem";
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
                "V0",
                "V1",
                "V2",
                "V3"
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;

            return std::make_pair(&Map[0], MapSize);
        }
    };

    /// @brief Values enumerator for
    ///     @ref tutorial21::field::Msg2FlagsMembers::EnumMem field.
    using EnumMemVal = EnumMemCommon::ValueType;

    /// @brief Common types and functions for
    ///     @ref tutorial21::field::Msg2FlagsMembers::IntMem field.
    struct IntMemCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial21::field::Msg2FlagsMembers::IntMem field.
        using ValueType = std::uint8_t;

        /// @brief Name of the @ref tutorial21::field::Msg2FlagsMembers::IntMem field.
        static const char* name()
        {
            return "IntMem";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial21::field::Msg2Flags field.
struct Msg2FlagsCommon
{
    /// @brief Name of the @ref tutorial21::field::Msg2Flags field.
    static const char* name()
    {
        return "Msg2Flags";
    }
};

} // namespace field

} // namespace tutorial21
