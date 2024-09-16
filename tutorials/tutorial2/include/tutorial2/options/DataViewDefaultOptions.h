// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = tutorial2::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for fields.
    struct field : public TBase::field
    {
        struct B8_1Members : public TBase::field::B8_1Members
        {
            /// @brief Extra options for @ref
            ///     tutorial2::field::B8_1Members::M3 field.
            using M3 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::field::B8_1Members::M3
                >;
        }; // struct B8_1Members

        struct B8_2Members : public TBase::field::B8_2Members
        {
            /// @brief Extra options for @ref
            ///     tutorial2::field::B8_2Members::M3 field.
            using M3 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::field::B8_2Members::M3
                >;
        }; // struct B8_2Members

        /// @brief Extra options for @ref
        ///     tutorial2::field::D7_1 field.
        using D7_1 =
            std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::field::D7_1
            >;

        /// @brief Extra options for @ref
        ///     tutorial2::field::D7_2 field.
        using D7_2 =
            std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::field::D7_2
            >;

        struct L10_3Members : public TBase::field::L10_3Members
        {
            struct ElementMembers : public TBase::field::L10_3Members::ElementMembers
            {
                /// @brief Extra options for @ref
                ///     tutorial2::field::L10_3Members::ElementMembers::M2
                ///     field.
                using M2 =
                    std::tuple<
                        comms::option::app::OrigDataView,
                        typename TBase::field::L10_3Members::ElementMembers::M2
                    >;
            }; // struct ElementMembers
        }; // struct L10_3Members

        struct L10_4Members : public TBase::field::L10_4Members
        {
            struct ElementMembers : public TBase::field::L10_4Members::ElementMembers
            {
                /// @brief Extra options for @ref
                ///     tutorial2::field::L10_4Members::ElementMembers::M3
                ///     field.
                using M3 =
                    std::tuple<
                        comms::option::app::OrigDataView,
                        typename TBase::field::L10_4Members::ElementMembers::M3
                    >;
            }; // struct ElementMembers
        }; // struct L10_4Members

        /// @brief Extra options for @ref
        ///     tutorial2::field::S6_1 field.
        using S6_1 =
            std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::field::S6_1
            >;

        /// @brief Extra options for @ref
        ///     tutorial2::field::S6_2 field.
        using S6_2 =
            std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::field::S6_2
            >;

        /// @brief Extra options for @ref
        ///     tutorial2::field::S6_3 field.
        using S6_3 =
            std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::field::S6_3
            >;

        /// @brief Extra options for @ref
        ///     tutorial2::field::S6_4 field.
        using S6_4 =
            std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::field::S6_4
            >;
    }; // struct field

    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref tutorial2::message::Msg18 message.
        struct Msg18Fields : public TBase::message::Msg18Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial2::message::Msg18Fields::F1
            ///     field.
            using F1 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg18Fields::F1
                >;
        };

        /// @brief Extra options for fields of
        ///     @ref tutorial2::message::Msg6 message.
        struct Msg6Fields : public TBase::message::Msg6Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial2::message::Msg6Fields::F5
            ///     field.
            using F5 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg6Fields::F5
                >;
        };

        /// @brief Extra options for fields of
        ///     @ref tutorial2::message::Msg7 message.
        struct Msg7Fields : public TBase::message::Msg7Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial2::message::Msg7Fields::F3
            ///     field.
            using F3 =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::message::Msg7Fields::F3
                >;
        };
    }; // struct message

    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref tutorial2::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial2::frame::FrameLayers::Data
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

} // namespace tutorial2
