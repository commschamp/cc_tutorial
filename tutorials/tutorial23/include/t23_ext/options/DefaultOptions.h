// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace t23_ext
{

namespace options
{

/// @brief Empty class to serve as the base for options.
struct EmptyOptions {};

/// @brief Default (empty) options of the protocol.
template <typename TBase = EmptyOptions>
struct DefaultOptionsT : public TBase
{
    struct t23_ext
    {
        /// @brief Extra options for namespace.
        struct ns1
        {
            /// @brief Extra options for fields.
            struct field
            {
                /// @brief Extra options for @ref
                ///     t23_ext::ns1::field::S1 field.
                using S1 = comms::option::app::EmptyOption;
            }; // struct field
        }; // struct ns1
    }; // struct t23_ext
};

/// @brief Default (empty) options of the protocol.
using DefaultOptions = DefaultOptionsT<>;

} // namespace options

} // namespace t23_ext
