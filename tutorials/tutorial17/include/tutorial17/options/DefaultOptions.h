// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial17
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
        ///     @ref tutorial17::message::Msg2 message.
        struct Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial17::message::Msg2Fields::F1
            ///     field.
            using F1 = comms::option::EmptyOption;
            
        };
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial17::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial17::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     tutorial17::frame::FrameLayers::SizeWithFlags
            ///     layer.
            using SizeWithFlags = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     tutorial17::frame::FrameLayers::IdWithFlags
            ///     layer.
            using IdWithFlags = comms::option::EmptyOption;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace tutorial17
