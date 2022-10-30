// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial9/options/DefaultOptions.h"

namespace tutorial9
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial9::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg1 message.
        using Msg1 =
            std::tuple<
                comms::option::app::NoReadImpl,
                comms::option::app::NoDispatchImpl,
                typename TBase::message::Msg1
            >;

        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg2 message.
        using Msg2 =
            std::tuple<
                comms::option::app::NoWriteImpl,
                comms::option::app::NoRefreshImpl,
                typename TBase::message::Msg2
            >;

        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg3 message.
        using Msg3 =
            std::tuple<
                comms::option::app::NoReadImpl,
                comms::option::app::NoDispatchImpl,
                typename TBase::message::Msg3
            >;

        /// @brief Extra options for @ref
        ///     tutorial9::message::Msg4 message.
        using Msg4 =
            std::tuple<
                comms::option::app::NoWriteImpl,
                comms::option::app::NoRefreshImpl,
                typename TBase::message::Msg4
            >;
    }; // struct message
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial9
