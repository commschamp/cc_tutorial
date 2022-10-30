// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of protocol client default options.

#pragma once

#include "t23_ext/options/DefaultOptions.h"

namespace t23_ext
{

namespace options
{

/// @brief Default client options of the protocol.
template <typename TBase = t23_ext::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace t23_ext
