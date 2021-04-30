// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial19::frame::Frame frame.

#pragma once

#include <cstdint>

namespace tutorial19
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial19::frame::Frame frame.
/// @see tutorial19::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial19::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial19::frame::FrameLayers::SizeMembers::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial19::frame::FrameLayers::SizeMembers::Field field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial19::frame::FrameLayers::SizeMembers::Field field.
            static const char* name()
            {
                return "Size";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial19::frame::FrameLayers::VersionMembers struct.
    struct VersionMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial19::frame::FrameLayers::VersionMembers::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial19::frame::FrameLayers::VersionMembers::Field field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial19::frame::FrameLayers::VersionMembers::Field field.
            static const char* name()
            {
                return "Version";
            }
            
        };
        
    };
    
};
} // namespace frame

} // namespace tutorial19


