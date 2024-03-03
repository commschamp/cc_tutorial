// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial23/options/DefaultOptions.h"

namespace tutorial23
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial23::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial23
