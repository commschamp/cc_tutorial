// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial12/options/DefaultOptions.h"

namespace tutorial12
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial12::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial12
