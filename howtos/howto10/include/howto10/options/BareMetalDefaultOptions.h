// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of protocol bare metal default options.

#pragma once

#include "howto10/options/DefaultOptions.h"

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

namespace howto10
{

namespace options
{

/// @brief Default bare metal options of the protocol.
template <typename TBase = howto10::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
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
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
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
            ///     howto10::frame::FrameLayers::DataMembers::Field field.
            struct DataMembers : public TBase::frame::FrameLayers::DataMembers
            {
                using Field =
                    std::tuple<
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                        typename TBase::frame::FrameLayers::DataMembers::Field
                    >;
            }; // struct DataMembers

            /// @brief Extra options for @ref
            ///     howto10::frame::FrameLayers::Id layer.
            using Id =
                std::tuple<
                    comms::option::app::InPlaceAllocation,
                    typename TBase::frame::FrameLayers::Id
                >;
        }; // struct FrameLayers
    }; // struct frame
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace howto10
