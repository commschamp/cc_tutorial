// Generated by commsdsl2comms v3.3.3

/// @file
/// @brief Contains definition of <b>"D7_1"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/ArrayList.h"
#include "comms/options.h"
#include "tutorial2/field/D7_1Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"D7_1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
struct D7_1 : public
    comms::field::ArrayList<
        tutorial2::field::FieldBase<>,
        std::uint8_t,
        TExtraOpts...,
        typename TOpt::field::D7_1,
        comms::option::def::SequenceFixedSize<5U>
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::D7_1Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2

