// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial15::frame::Frame frame.

#pragma once

#include <cstdint>

namespace tutorial15
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial15::frame::Frame frame.
/// @see tutorial15::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial15::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial15::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial15::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial15::frame::FrameLayers::SizeMembers::SizeField field.
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

} // namespace tutorial15
