// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg2 message and its fields.

#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>
#include "tutorial2/field/E2_1Common.h"
#include "tutorial2/field/E2_2Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg2 message.
/// @see tutorial2::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F1 field.
    struct F1Common : public tutorial2::field::E2_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F2 field.
    struct F2Common : public tutorial2::field::E2_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F3 field.
    struct F3Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::message::Msg2Fields::F3 field.
        enum class ValueType : std::int8_t
        {
            V1 = -100, ///< value @b V1. 
            V2 = 0, ///< value @b V2. 
            V3 = 10, ///< value @b V3. 

            // --- Extra values generated for convenience ---
            FirstValue = -100, ///< First defined value.
            LastValue = 10, ///< Last defined value.
            ValuesLimit = 11, ///< Upper limit for defined values.
        };

        /// @brief Single value name info entry
        using ValueNameInfo = std::pair<ValueType, const char*>;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F3 field.
        static const char* name()
        {
            return "F3";
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
    ///     @ref tutorial2::message::Msg2Fields::F3 field.
    using F3Val = F3Common::ValueType;

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F4 field.
    struct F4Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::message::Msg2Fields::F4 field.
        enum class ValueType : std::uint16_t
        {
            V1 = 0x0000U, ///< value <b>Value 1</b>. 
            V2 = 0x00FFU, ///< value <b>Value 2</b>. 
            V3 = 0x02FFU, ///< value <b>Value 3</b>. 
            V4 = 0x0FFFU, ///< value <b>Value 4</b>. 

            // --- Extra values generated for convenience ---
            FirstValue = 0x0000U, ///< First defined value.
            LastValue = 0x0FFFU, ///< Last defined value.
            ValuesLimit = 0x1000U, ///< Upper limit for defined values.
        };

        /// @brief Single value name info entry
        using ValueNameInfo = std::pair<ValueType, const char*>;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F4 field.
        static const char* name()
        {
            return "F4";
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
                std::make_pair(ValueType::V1, "Value 1"),
                std::make_pair(ValueType::V2, "Value 2"),
                std::make_pair(ValueType::V3, "Value 3"),
                std::make_pair(ValueType::V4, "Value 4")
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;

            return std::make_pair(&Map[0], MapSize);
        }
    };

    /// @brief Values enumerator for
    ///     @ref tutorial2::message::Msg2Fields::F4 field.
    using F4Val = F4Common::ValueType;
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref tutorial2::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace tutorial2
