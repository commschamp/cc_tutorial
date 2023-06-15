// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"SyncField"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "howto9/field/FieldBase.h"
#include "howto9/field/SyncFieldCommon.h"
#include "howto9/options/DefaultOptions.h"

namespace howto9
{

namespace field
{

/// @brief Definition of <b>"SyncField"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto9::options::DefaultOptions, typename... TExtraOpts>
class SyncField : public
    comms::field::IntValue<
        howto9::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...,
        comms::option::def::DefaultNumValue<43981L>
    >
{
    using Base =
        comms::field::IntValue<
            howto9::field::FieldBase<>,
            std::uint16_t,
            TExtraOpts...,
            comms::option::def::DefaultNumValue<43981L>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return howto9::field::SyncFieldCommon::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto9::field::SyncFieldCommon::name();
    }
};

} // namespace field

} // namespace howto9
