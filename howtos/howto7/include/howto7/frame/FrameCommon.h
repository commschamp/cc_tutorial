// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto7::frame::Frame frame.

#pragma once

#include <cstdint>

namespace howto7
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref howto7::frame::Frame frame.
/// @see howto7::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto7::frame::FrameLayers::AlternatingSyncMembers struct.
    struct AlternatingSyncMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto7::frame::FrameLayers::AlternatingSyncMembers::SyncField field.
        struct SyncFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto7::frame::FrameLayers::AlternatingSyncMembers::SyncField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref howto7::frame::FrameLayers::AlternatingSyncMembers::SyncField field.
            static const char* name()
            {
                return "SyncField";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto7::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto7::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto7::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref howto7::frame::FrameLayers::SizeMembers::SizeField field.
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
};

} // namespace frame

} // namespace howto7
