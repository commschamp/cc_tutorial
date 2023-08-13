// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of <b>"S6_4"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/S6_4Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"S6_4"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S6_4 : public
    comms::field::String<
        tutorial2::field::FieldBase<>,
        TExtraOpts...,
        typename TOpt::field::S6_4,
        comms::option::def::SequenceTerminationFieldSuffix<
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::ValidNumValueRange<0, 0>,
                comms::option::def::FailOnInvalid<>
            >
        >
    >
{
    using Base =
        comms::field::String<
            tutorial2::field::FieldBase<>,
            TExtraOpts...,
            typename TOpt::field::S6_4,
            comms::option::def::SequenceTerminationFieldSuffix<
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::ValidNumValueRange<0, 0>,
                    comms::option::def::FailOnInvalid<>
                >
            >
        >;
public:
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::S6_4Common::name();
    }
};

} // namespace field

} // namespace tutorial2
