// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol bare metal default options.

#pragma once

#include "t23_ext/options/DefaultOptions.h"

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

namespace t23_ext
{

namespace options
{

/// @brief Default bare metal options of the protocol.
template <typename TBase = t23_ext::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    struct t23_ext : public TBase::t23_ext
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
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                        typename TBase::t23_ext::ns1::field::S1
                    >;
            }; // struct field
        }; // struct ns1
    }; // struct t23_ext
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace t23_ext
