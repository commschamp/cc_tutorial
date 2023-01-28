// Generated by commsdsl2comms v5.2.0

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial11/options/DefaultOptions.h"

namespace tutorial11
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial11::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial11
