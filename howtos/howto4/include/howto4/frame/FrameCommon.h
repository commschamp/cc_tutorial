// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto4::frame::Frame frame.

#pragma once

#include <cstdint>

namespace howto4
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref howto4::frame::Frame frame.
/// @see howto4::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto4::frame::FrameLayers::SyncMembers struct.
    struct SyncMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto4::frame::FrameLayers::SyncMembers::SyncField field.
        struct SyncFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto4::frame::FrameLayers::SyncMembers::SyncField field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref howto4::frame::FrameLayers::SyncMembers::SyncField field.
            static const char* name()
            {
                return "SyncField";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto4::frame::FrameLayers::ChecksumMembers struct.
    struct ChecksumMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto4::frame::FrameLayers::ChecksumMembers::ChecksumField field.
        struct ChecksumFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto4::frame::FrameLayers::ChecksumMembers::ChecksumField field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref howto4::frame::FrameLayers::ChecksumMembers::ChecksumField field.
            static const char* name()
            {
                return "ChecksumField";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto4::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto4::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto4::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref howto4::frame::FrameLayers::SizeMembers::SizeField field.
            static const char* name()
            {
                return "SizeField";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto4::frame::FrameLayers::IdMembers struct.
    struct IdMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto4::frame::FrameLayers::IdMembers::IdField field.
        struct IdFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto4::frame::FrameLayers::IdMembers::IdField field.
            using ValueType = std::uint8_t;
        
            /// @brief Name of the @ref howto4::frame::FrameLayers::IdMembers::IdField field.
            static const char* name()
            {
                return "IdField";
            }
            
        };
        
    };
    
};
} // namespace frame

} // namespace howto4

