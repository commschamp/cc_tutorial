// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "howto8/options/DefaultOptions.h"

namespace howto8
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = howto8::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace howto8
