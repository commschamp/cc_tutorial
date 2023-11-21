// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial15/options/DefaultOptions.h"

namespace tutorial15
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial15::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for @ref
        ///     tutorial15::message::Msg1 message.
        using Msg1 =
            std::tuple<
                comms::option::app::NoWriteImpl,
                comms::option::app::NoRefreshImpl,
                typename TBase::message::Msg1
            >;
    }; // struct message
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial15
