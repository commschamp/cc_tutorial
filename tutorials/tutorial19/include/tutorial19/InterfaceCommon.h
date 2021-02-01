// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial19::Interface interface fields.

#pragma once

#include <cstdint>

namespace tutorial19
{

/// @brief Common types and functions for fields of 
///     @ref tutorial19::Interface interface.
/// @see tutorial19::InterfaceFields
struct InterfaceFieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial19::InterfaceFields::Version field.
    struct VersionCommon
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial19::InterfaceFields::Version field.
        using ValueType = std::uint16_t;
    
        /// @brief Name of the @ref tutorial19::InterfaceFields::Version field.
        static const char* name()
        {
            return "Version";
        }
        
    };
    
};
} // namespace tutorial19


