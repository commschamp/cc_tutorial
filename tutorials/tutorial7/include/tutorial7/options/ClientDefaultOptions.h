// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial7/options/DefaultOptions.h"

namespace tutorial7
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial7::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial7
