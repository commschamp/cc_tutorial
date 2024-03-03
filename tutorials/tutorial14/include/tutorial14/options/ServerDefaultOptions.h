// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial14/options/DefaultOptions.h"

namespace tutorial14
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial14::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial14
