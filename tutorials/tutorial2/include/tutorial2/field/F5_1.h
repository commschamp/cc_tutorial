// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains definition of <b>"F5_1"</b> field.

#pragma once

#include "comms/field/FloatValue.h"
#include "comms/options.h"
#include "tutorial2/field/F5_1Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"F5_1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
struct F5_1 : public
    comms::field::FloatValue<
        tutorial2::field::FieldBase<>,
        float,
        TExtraOpts...
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::F5_1Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2


