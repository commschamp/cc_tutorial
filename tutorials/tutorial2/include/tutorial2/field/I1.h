// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains definition of <b>"I1"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/I1Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"I1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
struct I1 : public
    comms::field::IntValue<
        tutorial2::field::FieldBase<>,
        std::uint8_t,
        TExtraOpts...
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::I1Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2


