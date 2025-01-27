// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Version"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial20/field/FieldBase.h"
#include "tutorial20/field/VersionCommon.h"
#include "tutorial20/options/DefaultOptions.h"

namespace tutorial20
{

namespace field
{

/// @brief Definition of <b>"Version"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial20::options::DefaultOptions, typename... TExtraOpts>
class Version : public
    comms::field::IntValue<
        tutorial20::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...,
        comms::option::def::HasName,
        comms::option::def::DefaultNumValue<5U>
    >
{
    using Base =
        comms::field::IntValue<
            tutorial20::field::FieldBase<>,
            std::uint16_t,
            TExtraOpts...,
            comms::option::def::HasName,
            comms::option::def::DefaultNumValue<5U>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return tutorial20::field::VersionCommon::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial20::field::VersionCommon::name();
    }
};

} // namespace field

} // namespace tutorial20
