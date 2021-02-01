// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of protocol default options for a client.

#pragma once

#include "DefaultOptions.h"

namespace tutorial1
{

namespace options
{

/// @brief Default options of the protocol for a client.
/// @tparam TBase Options to use as a basis.
template <typename TBase = tutorial1::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace tutorial1


