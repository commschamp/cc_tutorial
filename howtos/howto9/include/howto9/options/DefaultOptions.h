// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace howto9
{

namespace options
{

/// @brief Default (empty) options of the protocol.
struct DefaultOptions
{
    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for fields of
        ///     @ref howto9::message::Msg3 message.
        struct Msg3Fields
        {
            /// @brief Extra options for @ref
            ///     howto9::message::Msg3Fields::F1 field.
            using F1 = comms::option::EmptyOption;
            
        };
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref howto9::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto9::frame::FrameLayers::Data layer.
            using Data = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     howto9::frame::FrameLayers::Checksum
            ///     layer.
            using Checksum = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     howto9::frame::FrameLayers::Id layer.
            using Id = comms::option::EmptyOption;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace howto9
