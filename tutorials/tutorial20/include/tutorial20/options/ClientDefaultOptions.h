// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial20/options/DefaultOptions.h"

namespace tutorial20
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial20::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for @ref
        ///     tutorial20::message::Connect message.
        using Connect =
            std::tuple<
                comms::option::app::NoReadImpl,
                comms::option::app::NoDispatchImpl,
                typename TBase::message::Connect
            >;
    }; // struct message
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial20
