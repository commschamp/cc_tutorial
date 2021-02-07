// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial16::Interface interface fields.

#pragma once

#include "tutorial16/field/InterfaceFlagsCommon.h"

namespace tutorial16
{

/// @brief Common types and functions for fields of 
///     @ref tutorial16::Interface interface.
/// @see tutorial16::InterfaceFields
struct InterfaceFieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial16::InterfaceFields::Flags field.
    struct FlagsCommon : public tutorial16::field::InterfaceFlagsCommon
    {
        /// @brief Name of the @ref tutorial16::InterfaceFields::Flags field.
        static const char* name()
        {
            return "Flags";
        }
        
    };
    
};
} // namespace tutorial16


