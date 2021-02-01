// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of protocol default options for bare-metal application
///    where usage of dynamic memory allocation is disabled.

#pragma once

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

#include "howto2/options/DefaultOptions.h"

namespace howto2
{

namespace options
{

/// @brief Default options for bare-metal application where usage of dynamic
///    memory allocation is diabled.
/// @tparam TBase Options to use as a basis.
template <typename TBase = howto2::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref howto2::message::Msg1 message.
        struct Msg1Fields : public TBase::message::Msg1Fields
        {
            /// @brief Extra options for @ref
            ///     howto2::message::Msg1Fields::F1 field.
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                    typename TBase::message::Msg1Fields::F1
                >;
        }; // struct Msg1Fields
        
        
        /// @brief Extra options for fields of
        ///     @ref howto2::message::Msg3 message.
        struct Msg3Fields : public TBase::message::Msg3Fields
        {
            /// @brief Extra options for @ref
            ///     howto2::message::Msg3Fields::F1 field.
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                    typename TBase::message::Msg3Fields::F1
                >;
        }; // struct Msg3Fields
        
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for Layers of
        ///     @ref howto2::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto2::frame::FrameLayers::Data layer.
            using Data = std::tuple<
                comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                typename TBase::frame::FrameLayers::Data
            >;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace howto2


