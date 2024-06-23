// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial19/options/DefaultOptions.h"

namespace tutorial19
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial19::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial19::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial19::frame::FrameLayers::Data
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

} // namespace tutorial19
