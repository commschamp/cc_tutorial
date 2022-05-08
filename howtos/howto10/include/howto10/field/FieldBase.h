// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of base class of all the fields.

#pragma once

#include "comms/Field.h"
#include "comms/options.h"
#include "howto10/Version.h"

namespace howto10
{

namespace field
{

/// @brief Common base class for all the fields.
/// @tparam TOpt Extra options.
template <typename... TOpt>
using FieldBase =
    comms::Field<
        TOpt...,
        comms::option::def::BigEndian
    >;

} // namespace field

} // namespace howto10

