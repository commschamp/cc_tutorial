// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial13/options/DefaultOptions.h"

namespace tutorial13
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial13::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial13
