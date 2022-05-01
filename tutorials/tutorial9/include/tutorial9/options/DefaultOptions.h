// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial9
{

namespace options
{

/// @brief Default (empty) options of the protocol.
struct DefaultOptions
{
    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg1 message.
        using Msg1 = comms::option::EmptyOption;
        
        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg2 message.
        using Msg2 = comms::option::EmptyOption;
        
        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg3 message.
        using Msg3 = comms::option::EmptyOption;
        
        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg4 message.
        using Msg4 = comms::option::EmptyOption;
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial9::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial9::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     tutorial9::frame::FrameLayers::Id layer.
            using Id = comms::option::EmptyOption;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace tutorial9
