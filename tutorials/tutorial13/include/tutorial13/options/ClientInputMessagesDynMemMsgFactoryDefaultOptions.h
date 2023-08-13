// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of protocol client input messages dynamic memory allocation message factory options.

#pragma once

#include "tutorial13/factory/ClientInputMessagesDynMemMsgFactory.h"
#include "tutorial13/options/DefaultOptions.h"

namespace tutorial13
{

namespace options
{

/// @brief Provided client input messages dynamic memory allocation message factory options of the protocol.
/// @details Must be used as the outermost wrapper of the protocol options.
template <typename TBase = tutorial13::options::DefaultOptions>
struct ClientInputMessagesDynMemMsgFactoryDefaultOptionsT : public TBase
{
    /// @brief Alias to @ref tutorial13::factory::ClientInputMessagesDynMemMsgFactory message factory.
    /// @details Exposes the same template parameters as @b comms::MsgFactory.
    template <typename TInterface, typename TAllMessages, typename... TOptions>
    using MsgFactory = tutorial13::factory::ClientInputMessagesDynMemMsgFactory<TInterface, ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<TBase> >;

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial13::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial13::frame::FrameLayers::Id
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

} // namespace tutorial13
