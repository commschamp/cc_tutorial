// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial18/options/DefaultOptions.h"

namespace tutorial18
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial18::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial18::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial18::frame::FrameLayers::Data
            ///     layer.
            using Data =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::frame::FrameLayers::Data
                >;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace tutorial18
