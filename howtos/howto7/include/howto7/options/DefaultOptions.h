// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace howto7
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
        ///     @ref howto7::message::Msg3 message.
        struct Msg3Fields
        {
            /// @brief Extra options for @ref
            ///     howto7::message::Msg3Fields::F1 field.
            using F1 = comms::option::app::EmptyOption;
            
        }; // struct Msg3Fields
        
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for Layers of
        ///     @ref howto7::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto7::frame::FrameLayers::Data layer.
            using Data = comms::option::app::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     howto7::frame::FrameLayers::Id layer.
            using Id = comms::option::app::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     howto7::frame::FrameLayers::AlternatingSync
            ///     layer.
            using AlternatingSync = comms::option::app::EmptyOption;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace howto7


