// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of <b>"L6_3"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/L6_3Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"L6_3"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class L6_3 : public
    comms::field::IntValue<
        tutorial2::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...,
        comms::option::def::VarLength<1U, 2U>
    >
{
    using Base =
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint16_t,
            TExtraOpts...,
            comms::option::def::VarLength<1U, 2U>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return tutorial2::field::L6_3Common::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::L6_3Common::name();
    }
};

} // namespace field

} // namespace tutorial2
