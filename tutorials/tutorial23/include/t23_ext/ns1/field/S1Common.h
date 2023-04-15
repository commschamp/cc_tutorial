// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref t23_ext::ns1::field::S1 field.

#pragma once

#include <cstdint>

namespace t23_ext
{

namespace ns1
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref t23_ext::ns1::field::S1 field.
struct S1MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref t23_ext::ns1::field::S1Members::LengthPrefix field.
    struct LengthPrefixCommon
    {
        /// @brief Re-definition of the value type used by
        ///     t23_ext::ns1::field::S1Members::LengthPrefix field.
        using ValueType = std::uint8_t;

        /// @brief Name of the @ref t23_ext::ns1::field::S1Members::LengthPrefix field.
        static const char* name()
        {
            return "LengthPrefix";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions for
///     @ref t23_ext::ns1::field::S1 field.
struct S1Common
{
    /// @brief Name of the @ref t23_ext::ns1::field::S1 field.
    static const char* name()
    {
        return "S1";
    }
};

} // namespace field

} // namespace ns1

} // namespace t23_ext
