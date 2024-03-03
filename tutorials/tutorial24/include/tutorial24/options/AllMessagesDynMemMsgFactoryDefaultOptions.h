// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of protocol all messages dynamic memory allocation message factory options.

#pragma once

#include "tutorial24/factory/AllMessagesDynMemMsgFactory.h"
#include "tutorial24/options/DefaultOptions.h"

namespace tutorial24
{

namespace options
{

/// @brief Provided all messages dynamic memory allocation message factory options of the protocol.
/// @details Must be used as the outermost wrapper of the protocol options.
template <typename TBase = tutorial24::options::DefaultOptions>
struct AllMessagesDynMemMsgFactoryDefaultOptionsT : public TBase
{
    /// @brief Alias to @ref tutorial24::factory::AllMessagesDynMemMsgFactory message factory.
    /// @details Exposes the same template parameters as @b comms::MsgFactory.
    template <typename TInterface, typename TAllMessages, typename... TOptions>
    using MsgFactory = tutorial24::factory::AllMessagesDynMemMsgFactory<TInterface, AllMessagesDynMemMsgFactoryDefaultOptionsT<TBase> >;

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial24::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial24::frame::FrameLayers::Id
            ///     layer.
            using Id =
                std::tuple<
                    comms::option::app::MsgFactoryTempl<MsgFactory>,
                    typename TBase::frame::FrameLayers::Id
                >;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Alias to @ref AllMessagesDynMemMsgFactoryDefaultOptionsT with default template parameter.
using AllMessagesDynMemMsgFactoryDefaultOptions = AllMessagesDynMemMsgFactoryDefaultOptionsT<>;

} // namespace options

} // namespace tutorial24
