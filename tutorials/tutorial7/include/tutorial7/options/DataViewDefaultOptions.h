// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial7/options/DefaultOptions.h"

namespace tutorial7
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial7::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial7::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial7::frame::FrameLayers::Data
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

} // namespace tutorial7
