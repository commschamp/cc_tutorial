// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto5::field::VersionWithFlags field.

#pragma once

#include "howto5/field/InterfaceFlagsCommon.h"
#include "howto5/field/VersionCommon.h"

namespace howto5
{

namespace field
{


/// @brief Scope for all the common definitions of the member fields of
///     @ref howto5::field::VersionWithFlags field.
struct VersionWithFlagsMembersCommon
{
    /// @brief Common types and functions for
    ///     @ref howto5::field::VersionWithFlagsMembers::Version field.
    using VersionCommon = howto5::field::VersionCommon;
    
    /// @brief Common types and functions for
    ///     @ref howto5::field::VersionWithFlagsMembers::Flags field.
    struct FlagsCommon : public howto5::field::InterfaceFlagsCommon
    {
        /// @brief Name of the @ref howto5::field::VersionWithFlagsMembers::Flags field.
        static const char* name()
        {
            return "Flags";
        }
        
    };
    
};

/// @brief Common types and functions for
///     @ref howto5::field::VersionWithFlags field.
struct VersionWithFlagsCommon
{
    /// @brief Name of the @ref howto5::field::VersionWithFlags field.
    static const char* name()
    {
        return "VersionWithFlags";
    }
    
};

} // namespace field

} // namespace howto5

