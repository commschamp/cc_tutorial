// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial24::frame::Frame frame.

#pragma once

#include <cstdint>

namespace tutorial24
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial24::frame::Frame frame.
/// @see tutorial24::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial24::frame::FrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial24::frame::FrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial24::frame::FrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial24::frame::FrameLayers::SizeMembers::SizeField field.
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

} // namespace tutorial24
