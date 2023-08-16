// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "howto10/options/DefaultOptions.h"

namespace howto10
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = howto10::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace howto10
