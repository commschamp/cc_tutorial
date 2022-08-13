// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto2::frame::Frame frame.

#pragma once

#include <cstdint>
#include "howto2/field/MsgIdCommon.h"

namespace howto2
{

namespace frame
{


/// @brief Common types and functions of fields using in definition of
///     @ref howto2::frame::Frame frame.
/// @see howto2::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto2::frame::FrameLayers::IdWithSizeMembers struct.
    struct IdWithSizeMembersCommon
    {
        /// @brief Scope for all the common definitions of the member fields of
        ///     @ref howto2::frame::FrameLayers::IdWithSizeMembers::Field field.
        struct FieldMembersCommon
        {
            /// @brief Common types and functions for
            ///     @ref howto2::frame::FrameLayers::IdWithSizeMembers::FieldMembers::Size field.
            struct SizeCommon
            {
                /// @brief Re-definition of the value type used by
                ///     howto2::frame::FrameLayers::IdWithSizeMembers::FieldMembers::Size field.
                using ValueType = std::uint16_t;
                
                /// @brief Name of the @ref howto2::frame::FrameLayers::IdWithSizeMembers::FieldMembers::Size field.
                static const char* name()
                {
                    return "Size";
                }
                
                /// @brief Compile time detection of special values presence.
                static constexpr bool hasSpecials()
                {
                    return false;
                }
                
                
            };
            
            /// @brief Common types and functions for
            ///     @ref howto2::frame::FrameLayers::IdWithSizeMembers::FieldMembers::MsgId field.
            using MsgIdCommon = howto2::field::MsgIdCommon;
            
        };
        
        /// @brief Common types and functions for
        ///     @ref howto2::frame::FrameLayers::IdWithSizeMembers::Field field.
        struct FieldCommon
        {
            /// @brief Name of the @ref howto2::frame::FrameLayers::IdWithSizeMembers::Field field.
            static const char* name()
            {
                return "Field";
            }
            
        };
        
    };
    
};

} // namespace frame

} // namespace howto2


