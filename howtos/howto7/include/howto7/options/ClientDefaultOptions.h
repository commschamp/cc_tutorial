// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "howto7/options/DefaultOptions.h"

namespace howto7
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = howto7::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace howto7
