// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial2::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial2
