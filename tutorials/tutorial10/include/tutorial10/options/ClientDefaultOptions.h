// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial10/options/DefaultOptions.h"

namespace tutorial10
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial10::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for @ref
        ///     tutorial10::message::Msg1 message.
        using Msg1 =
            std::tuple<
                comms::option::app::NoReadImpl,
                comms::option::app::NoDispatchImpl,
                typename TBase::message::Msg1
            >;

        /// @brief Extra options for @ref
        ///     tutorial10::message::Msg2 message.
        using Msg2 =
            std::tuple<
                comms::option::app::NoWriteImpl,
                comms::option::app::NoRefreshImpl,
                typename TBase::message::Msg2
            >;
    }; // struct message
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial10
