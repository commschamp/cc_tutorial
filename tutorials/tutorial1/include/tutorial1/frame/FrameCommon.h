// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    fields used in definition of @ref tutorial1::frame::Frame frame.

#pragma once

#include "tutorial1/field/MsgIdCommon.h"

namespace tutorial1
{

namespace frame
{

/// @brief Common types and functions of fields using in definition of
///     @ref tutorial1::frame::Frame frame.
/// @see tutorial1::frame::FrameLayers
struct FrameLayersCommon
{
    /// @brief Scope for all the common definitions of the fields defined in
    ///     @ref tutorial1::frame::FrameLayers::IDMembers struct.
    struct IDMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial1::frame::FrameLayers::IDMembers::MsgId field.
        using MsgIdCommon = tutorial1::field::MsgIdCommon;
        
    };
    
};
} // namespace frame

} // namespace tutorial1


