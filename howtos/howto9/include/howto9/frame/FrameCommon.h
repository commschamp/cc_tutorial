// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto9::frame::Frame frame.

#pragma once

#include <cstdint>

namespace howto9
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref howto9::frame::Frame frame.
/// @see howto9::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto9::frame::FrameLayers::ChecksumMembers struct.
    struct ChecksumMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto9::frame::FrameLayers::ChecksumMembers::ChecksumField field.
        struct ChecksumFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto9::frame::FrameLayers::ChecksumMembers::ChecksumField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref howto9::frame::FrameLayers::ChecksumMembers::ChecksumField field.
            static const char* name()
            {
                return "ChecksumField";
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

} // namespace howto9
