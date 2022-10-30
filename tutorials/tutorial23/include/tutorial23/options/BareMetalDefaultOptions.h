// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol bare metal default options.

#pragma once

#include "tutorial23/options/DefaultOptions.h"

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

namespace tutorial23
{

namespace options
{

/// @brief Default bare metal options of the protocol.
template <typename TBase = tutorial23::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    struct tutorial23
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
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                        typename TBase::tutorial23::frame::FrameLayers::Data
                    >;

                /// @brief Extra options for @ref
                ///     tutorial23::frame::FrameLayers::Id
                ///     layer.
                using Id =
                    std::tuple<
                        comms::option::app::InPlaceAllocation,
                        typename TBase::tutorial23::frame::FrameLayers::Id
                    >;
            }; // struct FrameLayers
        }; // struct frame
    }; // struct tutorial23
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace tutorial23
