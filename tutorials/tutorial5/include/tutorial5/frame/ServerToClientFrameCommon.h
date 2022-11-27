// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial5::frame::ServerToClientFrame frame.

#pragma once

#include <cstdint>

namespace tutorial5
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial5::frame::ServerToClientFrame frame.
/// @see tutorial5::frame::ServerToClientFrameLayers
struct ServerToClientFrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial5::frame::ServerToClientFrameLayers::SizeMembers struct.
    struct SizeMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial5::frame::ServerToClientFrameLayers::SizeMembers::SizeField field.
        struct SizeFieldCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial5::frame::ServerToClientFrameLayers::SizeMembers::SizeField field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial5::frame::ServerToClientFrameLayers::SizeMembers::SizeField field.
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

} // namespace tutorial5
