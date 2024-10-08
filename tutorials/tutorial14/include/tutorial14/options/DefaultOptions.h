// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial14
{

namespace options
{

/// @brief Empty class to serve as the base for options.
struct EmptyOptions {};

/// @brief Default (empty) options of the protocol.
template <typename TBase = EmptyOptions>
struct DefaultOptionsT : public TBase
{
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial14::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial14::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::EmptyOption;

            /// @brief Extra options for @ref
            ///     tutorial14::frame::FrameLayers::Id
            ///     layer.
            using Id = comms::option::EmptyOption;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace tutorial14
