// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::B8_2 field.

#pragma once

#include <cstdint>
#include <type_traits>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::B8_2 field.
struct B8_2MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::B8_2Members::M1 field.
    struct M1Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::B8_2Members::M1 field.
        using ValueType = float;

        /// @brief Name of the @ref tutorial2::field::B8_2Members::M1 field.
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
    ///     @ref tutorial2::field::B8_2Members::M2 field.
    struct M2Common
    {
        /// @brief Name of the @ref tutorial2::field::B8_2Members::M2 field.
        static const char* name()
        {
            return "M2";
        }

        /// @brief Retrieve name of the bit of
        ///     @ref tutorial2::field::B8_2Members::M2 field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "SomeBit",
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                "SomeOtherbit"
            };

            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }

            return Map[idx];
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::field::B8_2Members::M3 field.
    struct M3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::field::B8_2Members::M3Members::Length field.
        struct LengthCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::field::B8_2Members::M3Members::Length field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial2::field::B8_2Members::M3Members::Length field.
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
    ///     @ref tutorial2::field::B8_2Members::M3 field.
    struct M3Common
    {
        /// @brief Name of the @ref tutorial2::field::B8_2Members::M3 field.
        static const char* name()
        {
            return "M3";
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial2::field::B8_2 field.
struct B8_2Common
{
    /// @brief Name of the @ref tutorial2::field::B8_2 field.
    static const char* name()
    {
        return "B8_2";
    }
};

} // namespace field

} // namespace tutorial2
