// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace howto4
{

namespace options
{

/// @brief Empty class to serve as the base for options.
struct EmptyOptions {};

/// @brief Default (empty) options of the protocol.
template <typename TBase = EmptyOptions>
struct DefaultOptionsT : public TBase
{
    /// @brief Extra options for fields.
    struct field
    {
        struct TlvPropMembers
        {
            struct Prop3Members
            {
                /// @brief Extra options for @ref
                ///     howto4::field::TlvPropMembers::Prop3Members::Val
                ///     field.
                using Val = comms::option::EmptyOption;
                
            }; // struct Prop3Members
            
            struct AnyMembers
            {
                /// @brief Extra options for @ref
                ///     howto4::field::TlvPropMembers::AnyMembers::Val
                ///     field.
                using Val = comms::option::EmptyOption;
                
            }; // struct AnyMembers
            
        }; // struct TlvPropMembers
        
    }; // struct field
    
    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for fields of
        ///     @ref howto4::message::Msg message.
        struct MsgFields
        {
            /// @brief Extra options for @ref
            ///     howto4::message::MsgFields::Props field.
            using Props = comms::option::EmptyOption;
            
        };
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref howto4::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto4::frame::FrameLayers::Data layer.
            using Data = comms::option::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     howto4::frame::FrameLayers::Id layer.
            using Id = comms::option::EmptyOption;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace howto4
