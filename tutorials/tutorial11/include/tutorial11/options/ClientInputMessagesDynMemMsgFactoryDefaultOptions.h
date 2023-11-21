// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol client input messages dynamic memory allocation message factory options.

#pragma once

#include "tutorial11/factory/ClientInputMessagesDynMemMsgFactory.h"
#include "tutorial11/options/DefaultOptions.h"

namespace tutorial11
{

namespace options
{

/// @brief Provided client input messages dynamic memory allocation message factory options of the protocol.
/// @details Must be used as the outermost wrapper of the protocol options.
template <typename TBase = tutorial11::options::DefaultOptions>
struct ClientInputMessagesDynMemMsgFactoryDefaultOptionsT : public TBase
{
    /// @brief Alias to @ref tutorial11::factory::ClientInputMessagesDynMemMsgFactory message factory.
    /// @details Exposes the same template parameters as @b comms::MsgFactory.
    template <typename TInterface, typename TAllMessages, typename... TOptions>
    using MsgFactory = tutorial11::factory::ClientInputMessagesDynMemMsgFactory<TInterface, ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<TBase> >;

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial11::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial11::frame::FrameLayers::Id
            ///     layer.
            using Id =
                std::tuple<
                    comms::option::app::MsgFactoryTempl<MsgFactory>,
                    typename TBase::frame::FrameLayers::Id
                >;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Alias to @ref ClientInputMessagesDynMemMsgFactoryDefaultOptionsT with default template parameter.
using ClientInputMessagesDynMemMsgFactoryDefaultOptions = ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<>;

} // namespace options

} // namespace tutorial11
