// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of protocol default options for a server.

#pragma once

#include "DefaultOptions.h"

namespace tutorial14
{

namespace options
{

/// @brief Default options of the protocol for a server.
/// @tparam TBase Options to use as a basis.
template <typename TBase = tutorial14::options::DefaultOptions>
struct ServerDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ServerDefaultOptionsT with default template parameter.
using ServerDefaultOptions = ServerDefaultOptionsT<>;

} // namespace options

} // namespace tutorial14


