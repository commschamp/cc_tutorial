// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial20::message::Msg2 message and its fields.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace tutorial20
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial20::message::Msg2 message.
/// @see tutorial20::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial20::message::Msg2Fields::F1 field.
    struct F1Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial20::message::Msg2Fields::F1 field.
        enum class ValueType : std::uint8_t
        {
            V0 = 0, ///< value @b V0. 
            V1 = 1, ///< value @b V1. 
            V2 = 2, ///< value @b V2. 

            // --- Extra values generated for convenience ---
            FirstValue = 0, ///< First defined value.
            LastValue = 2, ///< Last defined value.
            ValuesLimit = 3, ///< Upper limit for defined values.
        };

        /// @brief Single value name info entry
        using ValueNameInfo = const char*;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial20::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
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
                "V2"
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;

            return std::make_pair(&Map[0], MapSize);
        }
    };

    /// @brief Values enumerator for
    ///     @ref tutorial20::message::Msg2Fields::F1 field.
    using F1Val = F1Common::ValueType;

    /// @brief Common types and functions for
    ///     @ref tutorial20::message::Msg2Fields::F2 field.
    struct F2Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial20::message::Msg2Fields::F2 field.
        enum class ValueType : std::uint8_t
        {
            V0 = 0, ///< value @b V0. 
            V1 = 1, ///< value @b V1. 
            V2 = 2, ///< value @b V2. 

            // --- Extra values generated for convenience ---
            FirstValue = 0, ///< First defined value.
            LastValue = 2, ///< Last defined value.
            ValuesLimit = 3, ///< Upper limit for defined values.
        };

        /// @brief Single value name info entry
        using ValueNameInfo = const char*;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using ValueNamesMapInfo = std::pair<const ValueNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial20::message::Msg2Fields::F2 field.
        static const char* name()
        {
            return "F2";
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
                "V2"
            };
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;

            return std::make_pair(&Map[0], MapSize);
        }
    };

    /// @brief Values enumerator for
    ///     @ref tutorial20::message::Msg2Fields::F2 field.
    using F2Val = F2Common::ValueType;
};

/// @brief Common types and functions of 
///     @ref tutorial20::message::Msg2 message.
struct Msg2Common
{
    /// @brief Name of the @ref tutorial20::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
};

} // namespace message

} // namespace tutorial20
