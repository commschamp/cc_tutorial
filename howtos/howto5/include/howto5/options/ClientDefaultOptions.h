// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = howto5::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace howto5
