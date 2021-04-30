// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains definition of <b>"Version"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "howto5/field/FieldBase.h"
#include "howto5/field/VersionCommon.h"
#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace field
{

/// @brief Definition of <b>"Version"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto5::options::DefaultOptions, typename... TExtraOpts>
struct Version : public
    comms::field::IntValue<
        howto5::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...,
        comms::option::def::DefaultNumValue<5U>
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return howto5::field::VersionCommon::name();
    }
    
};

} // namespace field

} // namespace howto5


