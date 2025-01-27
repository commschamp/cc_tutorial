// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "tutorial22/options/DefaultOptions.h"

namespace tutorial22
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = tutorial22::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial22