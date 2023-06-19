// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "howto10/options/DefaultOptions.h"

namespace howto10
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = howto10::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace howto10
