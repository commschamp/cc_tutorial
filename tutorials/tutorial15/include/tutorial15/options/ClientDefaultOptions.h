// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial15/options/DefaultOptions.h"

namespace tutorial15
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial15::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for @ref
        ///     tutorial15::message::Msg1 message.
        using Msg1 =
            std::tuple<
                comms::option::app::NoReadImpl,
                comms::option::app::NoDispatchImpl,
                typename TBase::message::Msg1
            >;
    }; // struct message
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial15
