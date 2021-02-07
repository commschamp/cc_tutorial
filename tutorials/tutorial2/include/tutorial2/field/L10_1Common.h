// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::L10_1 field.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::L10_1 list.
struct L10_1MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::L10_1Members::Element field.
    struct ElementCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::field::L10_1Members::Element field.
        using ValueType = std::uint32_t;
    
        /// @brief Name of the @ref tutorial2::field::L10_1Members::Element field.
        static const char* name()
        {
            return "Element";
        }
        
    };
    
};

/// @brief Scope for all the common definitions of the
///     @ref tutorial2::field::L10_1 field.
struct L10_1Common
{
    /// @brief Name of the @ref tutorial2::field::L10_1 field.
    static const char* name()
    {
        return "L10_1";
    }
    
};


} // namespace field

} // namespace tutorial2


