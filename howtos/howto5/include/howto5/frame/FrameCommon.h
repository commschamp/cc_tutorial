// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref howto5::frame::Frame frame.

#pragma once

#include <cstdint>

namespace howto5
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref howto5::frame::Frame frame.
/// @see howto5::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref howto5::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref howto5::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     howto5::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref howto5::frame::FrameLayers::SizeMembers::SizeField field.
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

} // namespace howto5
