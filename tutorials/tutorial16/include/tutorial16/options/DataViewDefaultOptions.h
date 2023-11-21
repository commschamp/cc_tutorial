// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial16/options/DefaultOptions.h"

namespace tutorial16
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial16::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref tutorial16::message::Msg2 message.
        struct Msg2Fields : public TBase::message::Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial16::message::Msg2Fields::F1
            ///     field.
            using F1 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg2Fields::F1
                >;
        };
    }; // struct message

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial16::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial16::frame::FrameLayers::Data
            ///     layer.
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

} // namespace tutorial16
