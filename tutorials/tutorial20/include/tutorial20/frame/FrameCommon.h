// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial20::frame::Frame frame.

#pragma once

#include <cstdint>

namespace tutorial20
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial20::frame::Frame frame.
/// @see tutorial20::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial20::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial20::frame::FrameLayers::SizeMembers::Field field.
        struct FieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial20::frame::FrameLayers::SizeMembers::Field field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial20::frame::FrameLayers::SizeMembers::Field field.
            static const char* name()
            {
                return "Size";
            }
            
        };
        
    };
    
};
} // namespace frame

} // namespace tutorial20


