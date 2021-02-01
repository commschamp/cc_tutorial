// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial17::Interface interface fields.

#pragma once

#include <type_traits>

namespace tutorial17
{

/// @brief Common types and functions for fields of 
///     @ref tutorial17::Interface interface.
/// @see tutorial17::InterfaceFields
struct InterfaceFieldsCommon
{
    /// @brief Common functions for
    ///     @ref tutorial17::InterfaceFields::Flags field.
    struct FlagsCommon
    {
        /// @brief Name of the @ref tutorial17::InterfaceFields::Flags field.
        static const char* name()
        {
            return "Flags";
        }
        
        /// @brief Retrieve name of the bit of
        ///     @ref tutorial17::InterfaceFields::Flags field.
        static const char* bitName(std::size_t idx)
        {
            static const char* Map[] = {
                "B0",
                "B1"
            };
        
            static const std::size_t MapSize = std::extent<decltype(Map)>::value;
            if (MapSize <= idx) {
                return nullptr;
            }
        
            return Map[idx];
        }
        
    };
    
};
} // namespace tutorial17


