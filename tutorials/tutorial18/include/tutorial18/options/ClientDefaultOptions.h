// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial18/options/DefaultOptions.h"

namespace tutorial18
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial18::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial18
