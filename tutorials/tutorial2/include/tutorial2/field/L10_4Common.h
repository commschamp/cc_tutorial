// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::L10_4 field.

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
///     @ref tutorial2::field::L10_4 field.
struct L10_4MembersCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::field::L10_4Members::Element field.
    struct ElementMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::field::L10_4Members::ElementMembers::M1 field.
        struct M1Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::field::L10_4Members::ElementMembers::M1 field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial2::field::L10_4Members::ElementMembers::M1 field.
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
        ///     @ref tutorial2::field::L10_4Members::ElementMembers::M2 field.
        struct M2Common
        {
            /// @brief Values enumerator for
            ///     @ref tutorial2::field::L10_4Members::ElementMembers::M2 field.
            enum class ValueType : std::uint8_t
            {
                V1 = 5, ///< value @b V1. 
                V2 = 15, ///< value @b V2. 

                // --- Extra values generated for convenience ---
                FirstValue = 5, ///< First defined value.
                LastValue = 15, ///< Last defined value.
                ValuesLimit = 16, ///< Upper limit for defined values.
            };

            /// @brief Single value name info entry
            using ValueNameInfo = std::pair<ValueType, const char*>;

            /// @brief Type returned from @ref valueNamesMap() member function.
            /// @details The @b first value of the pair is pointer to the map array,
            ///     The @b second value of the pair is the size of the array.
            using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;

            /// @brief Name of the @ref tutorial2::field::L10_4Members::ElementMembers::M2 field.
            static const char* name()
            {
                return "M2";
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
                    std::make_pair(ValueType::V2, "V2")
                };
                static const std::size_t MapSize = std::extent<decltype(Map)>::value;

                return std::make_pair(&Map[0], MapSize);
            }
        };

        /// @brief Values enumerator for
        ///     @ref tutorial2::field::L10_4Members::ElementMembers::M2 field.
        using M2Val = M2Common::ValueType;

        /// @brief Common types and functions for
        ///     @ref tutorial2::field::L10_4Members::ElementMembers::M3 field.
        struct M3Common
        {
            /// @brief Name of the @ref tutorial2::field::L10_4Members::ElementMembers::M3 field.
            static const char* name()
            {
                return "M3";
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_4Members::Element field.
    struct ElementCommon
    {
        /// @brief Name of the @ref tutorial2::field::L10_4Members::Element field.
        static const char* name()
        {
            return "Element";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_4Members::Size field.
    struct SizeCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::L10_4Members::Size field.
        using ValueType = std::uint16_t;

        /// @brief Name of the @ref tutorial2::field::L10_4Members::Size field.
        static const char* name()
        {
            return "Size";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_4Members::Length field.
    struct LengthCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::L10_4Members::Length field.
        using ValueType = std::uint8_t;

        /// @brief Name of the @ref tutorial2::field::L10_4Members::Length field.
        static const char* name()
        {
            return "Length";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial2::field::L10_4 field.
struct L10_4Common
{
    /// @brief Name of the @ref tutorial2::field::L10_4 field.
    static const char* name()
    {
        return "L10_4";
    }
};

} // namespace field

} // namespace tutorial2
