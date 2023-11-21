// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "howto10/options/DefaultOptions.h"

namespace howto10
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = howto10::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref howto10::message::Msg3 message.
        struct Msg3Fields : public TBase::message::Msg3Fields
        {
            /// @brief Extra options for @ref
            ///     howto10::message::Msg3Fields::F1 field.
            using F1 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg3Fields::F1
                >;
        };
    }; // struct message

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref howto10::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto10::frame::FrameLayers::Data layer.
            using Data =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::frame::FrameLayers::Data
                >;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace howto10
