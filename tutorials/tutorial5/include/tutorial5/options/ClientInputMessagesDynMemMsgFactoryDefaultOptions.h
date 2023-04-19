// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of protocol client input messages dynamic memory allocation message factory options.

#pragma once

#include "tutorial5/factory/ClientInputMessagesDynMemMsgFactory.h"
#include "tutorial5/options/DefaultOptions.h"

namespace tutorial5
{

namespace options
{

/// @brief Provided client input messages dynamic memory allocation message factory options of the protocol.
/// @details Must be used as the outermost wrapper of the protocol options.
template <typename TBase = tutorial5::options::DefaultOptions>
struct ClientInputMessagesDynMemMsgFactoryDefaultOptionsT : public TBase
{
    /// @brief Alias to @ref tutorial5::factory::ClientInputMessagesDynMemMsgFactory message factory.
    /// @details Exposes the same template parameters as @b comms::MsgFactory.
    template <typename TInterface, typename TAllMessages, typename... TOptions>
    using MsgFactory = tutorial5::factory::ClientInputMessagesDynMemMsgFactory<TInterface, ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<TBase> >;

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial5::frame::ClientToServerFrame frame.
        struct ClientToServerFrameLayers : public TBase::frame::ClientToServerFrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial5::frame::ClientToServerFrameLayers::Id
            ///     layer.
            using Id =
                std::tuple<
                    comms::option::app::MsgFactoryTempl<MsgFactory>,
                    typename TBase::frame::ClientToServerFrameLayers::Id
                >;
        }; // struct ClientToServerFrameLayers

        /// @brief Extra options for layers of
        ///     @ref tutorial5::frame::ServerToClientFrame frame.
        struct ServerToClientFrameLayers : public TBase::frame::ServerToClientFrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial5::frame::ServerToClientFrameLayers::Id
            ///     layer.
            using Id =
                std::tuple<
                    comms::option::app::MsgFactoryTempl<MsgFactory>,
                    typename TBase::frame::ServerToClientFrameLayers::Id
                >;
        }; // struct ServerToClientFrameLayers
    }; // struct frame
};

/// @brief Alias to @ref ClientInputMessagesDynMemMsgFactoryDefaultOptionsT with default template parameter.
using ClientInputMessagesDynMemMsgFactoryDefaultOptions = ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<>;

} // namespace options

} // namespace tutorial5
