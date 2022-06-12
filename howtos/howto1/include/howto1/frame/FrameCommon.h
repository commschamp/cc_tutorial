// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto1::frame::Frame frame.

#pragma once

#include <cstdint>
#include "howto1/field/InterfaceFlagsCommon.h"

namespace howto1
{

namespace frame
{


/// @brief Common types and functions of fields using in definition of
///     @ref howto1::frame::Frame frame.
/// @see howto1::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto1::frame::FrameLayers::SizeWithFlagsMembers struct.
    struct SizeWithFlagsMembersCommon
    {
        /// @brief Scope for all the common definitions of the member fields of
        ///     @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::Field field.
        struct FieldMembersCommon
        {
            /// @brief Common types and functions for
            ///     @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Size field.
            struct SizeCommon
            {
                /// @brief Re-definition of the value type used by
                ///     howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Size field.
                using ValueType = std::uint16_t;
                
                /// @brief Name of the @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Size field.
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
            ///     @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Flags field.
            struct FlagsCommon : public howto1::field::InterfaceFlagsCommon
            {
                /// @brief Name of the @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::FieldMembers::Flags field.
                static const char* name()
                {
                    return "Flags";
                }
                
            };
            
        };
        
        /// @brief Common types and functions for
        ///     @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::Field field.
        struct FieldCommon
        {
            /// @brief Name of the @ref howto1::frame::FrameLayers::SizeWithFlagsMembers::Field field.
            static const char* name()
            {
                return "Field";
            }
            
        };
        
    };
    
};

} // namespace frame

} // namespace howto1


