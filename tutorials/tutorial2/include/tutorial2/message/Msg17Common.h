// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg17 message and its fields.

#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg17 message.
/// @see tutorial2::message::Msg17Fields
struct Msg17FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg17Fields::F1 field.
    struct F1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg17Fields::F1 field.
        using ValueType = std::uint32_t;

        /// @brief Single special value name info entry.
        using SpecialNameInfo = std::pair<ValueType, const char*>;

        /// @brief Type returned from @ref specialNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using SpecialNamesMapInfo = std::pair<const SpecialNameInfo*, std::size_t>;

        /// @brief Name of the @ref tutorial2::message::Msg17Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return true;
        }

        /// @brief Special value <b>"S1"</b>.
        static constexpr ValueType valueS1()
        {
            return static_cast<ValueType>(10);
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

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg17Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg17Fields::F2Members::M1 field.
        struct M1Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg17Fields::F2Members::M1 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial2::message::Msg17Fields::F2Members::M1 field.
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
        ///     @ref tutorial2::message::Msg17Fields::F2Members::M2 field.
        struct M2Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg17Fields::F2Members::M2 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial2::message::Msg17Fields::F2Members::M2 field.
            static const char* name()
            {
                return "M2";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };

        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg17Fields::F2Members::M3 field.
        struct M3Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg17Fields::F2Members::M3 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial2::message::Msg17Fields::F2Members::M3 field.
            static const char* name()
            {
                return "M3";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg17Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg17Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg17 message.
struct Msg17Common
{
    /// @brief Name of the @ref tutorial2::message::Msg17 message.
    static const char* name()
    {
        return "Message 17";
    }
};

} // namespace message

} // namespace tutorial2
