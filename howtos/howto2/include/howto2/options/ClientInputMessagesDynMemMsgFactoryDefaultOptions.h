// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of protocol client input messages dynamic memory allocation message factory options.

#pragma once

#include "howto2/factory/ClientInputMessagesDynMemMsgFactory.h"
#include "howto2/options/DefaultOptions.h"

namespace howto2
{

namespace options
{

/// @brief Provided client input messages dynamic memory allocation message factory options of the protocol.
/// @details Must be used as the outermost wrapper of the protocol options.
template <typename TBase = howto2::options::DefaultOptions>
struct ClientInputMessagesDynMemMsgFactoryDefaultOptionsT : public TBase
{
    /// @brief Alias to @ref howto2::factory::ClientInputMessagesDynMemMsgFactory message factory.
    /// @details Exposes the same template parameters as @b comms::MsgFactory.
    template <typename TInterface, typename TAllMessages, typename... TOptions>
    using MsgFactory = howto2::factory::ClientInputMessagesDynMemMsgFactory<TInterface, ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<TBase> >;
};

/// @brief Alias to @ref ClientInputMessagesDynMemMsgFactoryDefaultOptionsT with default template parameter.
using ClientInputMessagesDynMemMsgFactoryDefaultOptions = ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<>;

} // namespace options

} // namespace howto2
