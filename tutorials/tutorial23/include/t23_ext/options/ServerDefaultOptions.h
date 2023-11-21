// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "t23_ext/options/DefaultOptions.h"

namespace t23_ext
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = t23_ext::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace t23_ext
