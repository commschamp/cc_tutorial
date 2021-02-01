// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial16::frame::Frame frame.

#pragma once

#include <cstdint>
#include "tutorial16/field/InterfaceFlagsCommon.h"

namespace tutorial16
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial16::frame::Frame frame.
/// @see tutorial16::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial16::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial16::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial16::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial16::frame::FrameLayers::SizeMembers::SizeField field.
            static const char* name()
            {
                return "SizeField";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial16::frame::FrameLayers::FlagsMembers struct.
    struct FlagsMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial16::frame::FrameLayers::FlagsMembers::Field field.
        struct FieldCommon : public tutorial16::field::InterfaceFlagsCommon
        {
            /// @brief Name of the @ref tutorial16::frame::FrameLayers::FlagsMembers::Field field.
            static const char* name()
            {
                return "Field";
            }
            
        };
        
    };
    
};
} // namespace frame

} // namespace tutorial16


