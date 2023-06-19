// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "howto7/options/DefaultOptions.h"

namespace howto7
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = howto7::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace howto7
