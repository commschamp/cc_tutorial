// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial4/options/DefaultOptions.h"

namespace tutorial4
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial4::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial4
