// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of <b>"I3_5"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/I3_5Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"I3_5"</b> field.
/// @details
///     Year as offset since 2000
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class I3_5 : public
    comms::field::IntValue<
        tutorial2::field::FieldBase<>,
        std::int16_t,
        TExtraOpts...,
        comms::option::def::FixedLength<1U>,
        comms::option::def::NumValueSerOffset<-2000>,
        comms::option::def::DefaultNumValue<2020>
    >
{
    using Base =
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::int16_t,
            TExtraOpts...,
            comms::option::def::FixedLength<1U>,
            comms::option::def::NumValueSerOffset<-2000>,
            comms::option::def::DefaultNumValue<2020>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return tutorial2::field::I3_5Common::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::I3_5Common::name();
    }
};

} // namespace field

} // namespace tutorial2
