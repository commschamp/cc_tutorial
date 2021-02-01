// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of protocol default options that apply
///     @b comms::option::app::OrigDataView to applicable fields.

#pragma once

#include "howto1/options/DefaultOptions.h"

namespace howto1
{

namespace options
{

/// @brief Default options for data view on contiguous buffers to avoid
///    unnecessary copy of data.
/// @tparam TBase Options to use as a basis.
template <typename TBase = howto1::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref howto1::message::Msg2 message.
        struct Msg2Fields : public TBase::message::Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     howto1::message::Msg2Fields::F1 field.
            using F1 = 
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg2Fields::F1
                >;
        }; // struct Msg2Fields
        
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for Layers of
        ///     @ref howto1::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto1::frame::FrameLayers::Data layer.
            using Data = std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::frame::FrameLayers::Data
            >;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace howto1


