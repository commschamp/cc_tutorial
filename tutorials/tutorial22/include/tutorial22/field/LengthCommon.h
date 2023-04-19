// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial22::field::Length field.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace tutorial22
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial22::field::Length field.
struct LengthMembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial22::field::LengthMembers::Short field.
    struct ShortCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial22::field::LengthMembers::Short field.
        using ValueType = std::uint8_t;

        /// @brief Single special value name info entry.
        using SpecialNameInfo = std::pair<ValueType, const char*>;

        /// @brief Type returned from @ref specialNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using SpecialNamesMapInfo = std::pair<const SpecialNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial22::field::LengthMembers::Short field.
        static const char* name()
        {
            return "Short";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return true;
        }

        /// @brief Special value <b>"LongForm"</b>.
        static constexpr ValueType valueLongForm()
        {
            return static_cast<ValueType>(255);
        }

        /// @brief Retrieve map of special value names
        static SpecialNamesMapInfo specialNamesMap()
        {
            static const SpecialNameInfo Map[] = {
                std::make_pair(valueLongForm(), "LongForm")
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;

            return std::make_pair(&Map[0], MapSize);
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial22::field::LengthMembers::Long field.
    struct LongMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial22::field::LengthMembers::LongMembers::ActLong field.
        struct ActLongCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial22::field::LengthMembers::LongMembers::ActLong field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial22::field::LengthMembers::LongMembers::ActLong field.
            static const char* name()
            {
                return "ActLong";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial22::field::LengthMembers::Long field.
    struct LongCommon
    {
        /// @brief Name of the @ref tutorial22::field::LengthMembers::Long field.
        static const char* name()
        {
            return "Long";
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial22::field::Length field.
struct LengthCommon
{
    /// @brief Name of the @ref tutorial22::field::Length field.
    static const char* name()
    {
        return "Length";
    }
};

} // namespace field

} // namespace tutorial22
