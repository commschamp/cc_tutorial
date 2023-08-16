// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial3/options/DefaultOptions.h"

namespace tutorial3
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial3::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial3
