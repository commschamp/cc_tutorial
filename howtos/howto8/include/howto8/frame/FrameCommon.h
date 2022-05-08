// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto8::frame::Frame frame.

#pragma once

#include <cstdint>
#include <type_traits>
#include "howto8/field/MsgIdCommon.h"

namespace howto8
{

namespace frame
{


/// @brief Common types and functions of fields using in definition of
///     @ref howto8::frame::Frame frame.
/// @see howto8::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto8::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto8::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto8::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;
            
            /// @brief Name of the @ref howto8::frame::FrameLayers::SizeMembers::SizeField field.
            static const char* name()
            {
                return "SizeField";
            }
            
            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
            
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto8::frame::FrameLayers::IdMembers struct.
    struct IdMembersCommon
    {
        /// @brief Scope for all the common definitions of the member fields of
        ///     @ref howto8::frame::FrameLayers::IdMembers::Field field.
        struct FieldMembersCommon
        {
            /// @brief Common types and functions for
            ///     @ref howto8::frame::FrameLayers::IdMembers::FieldMembers::MsgId field.
            using MsgIdCommon = howto8::field::MsgIdCommon;
            
            /// @brief Common types and functions for
            ///     @ref howto8::frame::FrameLayers::IdMembers::FieldMembers::Ctrl field.
            struct CtrlCommon
            {
                /// @brief Name of the @ref howto8::frame::FrameLayers::IdMembers::FieldMembers::Ctrl field.
                static const char* name()
                {
                    return "Ctrl";
                }
                
                /// @brief Retrieve name of the bit of
                ///     @ref howto8::frame::FrameLayers::IdMembers::FieldMembers::Ctrl field.
                static const char* bitName(std::size_t idx)
                {
                    static const char* Map[] = {
                        "HasFlags"
                    };
                
                    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
                    if (MapSize <= idx) {
                        return nullptr;
                    }
                
                    return Map[idx];
                }
                
                
            };
            
        };
        
        /// @brief Common types and functions for
        ///     @ref howto8::frame::FrameLayers::IdMembers::Field field.
        struct FieldCommon
        {
            /// @brief Name of the @ref howto8::frame::FrameLayers::IdMembers::Field field.
            static const char* name()
            {
                return "Field";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto8::frame::FrameLayers::FlagsMembers struct.
    struct FlagsMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto8::frame::FrameLayers::FlagsMembers::OptFlags field.
        struct OptFlagsCommon
        {
            /// @brief Name of the @ref howto8::frame::FrameLayers::FlagsMembers::OptFlags field.
            static const char* name()
            {
                return "OptFlags";
            }
            
        };
        
    };
    
};

} // namespace frame

} // namespace howto8


