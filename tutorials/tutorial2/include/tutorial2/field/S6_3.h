// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of <b>"S6_3"</b> field.

#pragma once

#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/L6_3.h"
#include "tutorial2/field/S6_3Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"S6_3"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S6_3 : public
    comms::field::String<
        tutorial2::field::FieldBase<>,
        TExtraOpts...,
        typename TOpt::field::S6_3,
        comms::option::def::SequenceSerLengthFieldPrefix<tutorial2::field::L6_3<TOpt> >
    >
{
    using Base =
        comms::field::String<
            tutorial2::field::FieldBase<>,
            TExtraOpts...,
            typename TOpt::field::S6_3,
            comms::option::def::SequenceSerLengthFieldPrefix<tutorial2::field::L6_3<TOpt> >
        >;
public:
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::S6_3Common::name();
    }
};

} // namespace field

} // namespace tutorial2
