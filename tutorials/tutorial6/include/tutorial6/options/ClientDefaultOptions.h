// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial6/options/DefaultOptions.h"

namespace tutorial6
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial6::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial6
