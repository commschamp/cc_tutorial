// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::F11_3 field.

#pragma once

#include "tutorial2/field/F11_1Common.h"
#include "tutorial2/field/F11_2Common.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial2::field::F11_3 field.
struct F11_3MembersCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::field::F11_3Members::M1 field.
    using M1Common = tutorial2::field::F11_1Common;

    /// @brief Common types and functions for
    ///     @ref tutorial2::field::F11_3Members::M2 field.
    struct M2Common : public tutorial2::field::F11_2Common
    {
        /// @brief Name of the @ref tutorial2::field::F11_3Members::M2 field.
        static const char* name()
        {
            return "M2";
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial2::field::F11_3 field.
struct F11_3Common
{
    /// @brief Name of the @ref tutorial2::field::F11_3 field.
    static const char* name()
    {
        return "F11_3";
    }
};

} // namespace field

} // namespace tutorial2
