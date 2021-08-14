// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial8::frame::Frame frame.

#pragma once

#include <cstdint>

namespace tutorial8
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial8::frame::Frame frame.
/// @see tutorial8::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial8::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial8::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial8::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial8::frame::FrameLayers::SizeMembers::SizeField field.
            static const char* name()
            {
                return "SizeField";
            }
            
        };
        
    };
    
};
} // namespace frame

} // namespace tutorial8


