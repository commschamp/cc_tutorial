// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto1::Interface interface fields.

#pragma once

#include "howto1/field/InterfaceFlagsCommon.h"

namespace howto1
{

/// @brief Common types and functions for fields of 
///     @ref howto1::Interface interface.
/// @see howto1::InterfaceFields
struct InterfaceFieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto1::InterfaceFields::Flags field.
    struct FlagsCommon : public howto1::field::InterfaceFlagsCommon
    {
        /// @brief Name of the @ref howto1::InterfaceFields::Flags field.
        static const char* name()
        {
            return "Flags";
        }
    };
};
} // namespace howto1
