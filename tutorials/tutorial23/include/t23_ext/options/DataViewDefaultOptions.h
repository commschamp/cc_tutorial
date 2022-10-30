// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "t23_ext/options/DefaultOptions.h"

namespace t23_ext
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = t23_ext::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    struct t23_ext
    {
        /// @brief Extra options for namespace.
        struct ns1: public TBase::t23_ext::ns1
        {
            /// @brief Extra options for fields.
            struct field : public TBase::t23_ext::ns1::field
            {
                /// @brief Extra options for @ref
                ///     t23_ext::ns1::field::S1 field.
                using S1 =
                    std::tuple<
                        comms::option::app::OrigDataView,
                        typename TBase::t23_ext::ns1::field::S1
                    >;
            }; // struct field
        }; // struct ns1
    }; // struct t23_ext
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace t23_ext
