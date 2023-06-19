// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial23/options/DefaultOptions.h"

namespace tutorial23
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial23::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    struct tutorial23 : public TBase::tutorial23
    {
        /// @brief Extra options for frames.
        struct frame : public TBase::tutorial23::frame
        {
            /// @brief Extra options for layers of
            ///     @ref tutorial23::frame::Frame frame.
            struct FrameLayers : public TBase::tutorial23::frame::FrameLayers
            {
                /// @brief Extra options for @ref
                ///     tutorial23::frame::FrameLayers::Data
                ///     layer.
                using Data =
                    std::tuple<
                        comms::option::app::OrigDataView,
                        typename TBase::tutorial23::frame::FrameLayers::Data
                    >;
            }; // struct FrameLayers
        }; // struct frame
    }; // struct tutorial23
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace tutorial23
