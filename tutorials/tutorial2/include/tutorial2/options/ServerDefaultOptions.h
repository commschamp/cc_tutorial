// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of protocol server default options.

#pragma once

#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace options
{

/// @brief Default server options of the protocol.
template <typename TBase = tutorial2::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial2
