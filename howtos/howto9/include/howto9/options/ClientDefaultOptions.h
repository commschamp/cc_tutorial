// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "howto9/options/DefaultOptions.h"

namespace howto9
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = howto9::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace howto9
