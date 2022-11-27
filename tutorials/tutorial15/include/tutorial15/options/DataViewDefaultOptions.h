// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial15/options/DefaultOptions.h"

namespace tutorial15
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial15::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref tutorial15::message::Msg2 message.
        struct Msg2Fields : public TBase::message::Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial15::message::Msg2Fields::F1
            ///     field.
            using F1 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg2Fields::F1
                >;
        };

        /// @brief Extra options for fields of
        ///     @ref tutorial15::message::Msg3 message.
        struct Msg3Fields : public TBase::message::Msg3Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial15::message::Msg3Fields::F1
            ///     field.
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
        ///     @ref tutorial15::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial15::frame::FrameLayers::Data
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

} // namespace tutorial15
