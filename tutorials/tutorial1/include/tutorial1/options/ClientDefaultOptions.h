// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial1/options/DefaultOptions.h"

namespace tutorial1
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial1::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial1
