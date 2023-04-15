// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of protocol bare metal default options.

#pragma once

#include "tutorial14/options/DefaultOptions.h"

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

namespace tutorial14
{

namespace options
{

/// @brief Default bare metal options of the protocol.
template <typename TBase = tutorial14::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial14::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial14::frame::FrameLayers::Data
            ///     layer.
            using Data =
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                    typename TBase::frame::FrameLayers::Data
                >;

            /// @brief Extra options for @ref
            ///     tutorial14::frame::FrameLayers::Id
            ///     layer.
            using Id =
                std::tuple<
                    comms::option::app::InPlaceAllocation,
                    typename TBase::frame::FrameLayers::Id
                >;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace tutorial14
