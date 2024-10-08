// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial5/options/DefaultOptions.h"

namespace tutorial5
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial5::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial5::frame::ClientToServerFrame frame.
        struct ClientToServerFrameLayers : public TBase::frame::ClientToServerFrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial5::frame::ClientToServerFrameLayers::Data
            ///     layer.
            using Data =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::frame::ClientToServerFrameLayers::Data
                >;
        }; // struct ClientToServerFrameLayers

        /// @brief Extra options for layers of
        ///     @ref tutorial5::frame::ServerToClientFrame frame.
        struct ServerToClientFrameLayers : public TBase::frame::ServerToClientFrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial5::frame::ServerToClientFrameLayers::Data
            ///     layer.
            using Data =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::frame::ServerToClientFrameLayers::Data
                >;
        }; // struct ServerToClientFrameLayers
    }; // struct frame
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace tutorial5
