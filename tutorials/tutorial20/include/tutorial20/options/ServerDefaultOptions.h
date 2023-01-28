// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial20/options/DefaultOptions.h"

namespace tutorial20
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial20::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for @ref
        ///     tutorial20::message::Connect message.
        using Connect =
            std::tuple<
                comms::option::app::NoWriteImpl,
                comms::option::app::NoRefreshImpl,
                typename TBase::message::Connect
            >;
    }; // struct message
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial20
