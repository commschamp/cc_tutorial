// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial14
{

namespace options
{

/// @brief Default (empty) options of the protocol.
struct DefaultOptions
{
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial14::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial14::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     tutorial14::frame::FrameLayers::Id
            ///     layer.
            using Id = comms::option::EmptyOption;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace tutorial14
