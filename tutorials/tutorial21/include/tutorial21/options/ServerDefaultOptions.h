// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial21::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial21
