// Generated by commsdsl2comms v6.3.4

/// @file
/// @brief Contains definition of <b>"Flags"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial21/field/BasicFlagsCommon.h"
#include "tutorial21/field/FieldBase.h"
#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace field
{

/// @brief Definition of <b>"Flags"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial21::options::DefaultOptions, typename... TExtraOpts>
class BasicFlags : public
    comms::field::IntValue<
        tutorial21::field::FieldBase<>,
        std::uint8_t,
        TExtraOpts...
    >
{
    using Base =
        comms::field::IntValue<
            tutorial21::field::FieldBase<>,
            std::uint8_t,
            TExtraOpts...
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return tutorial21::field::BasicFlagsCommon::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial21::field::BasicFlagsCommon::name();
    }
};

} // namespace field

} // namespace tutorial21
