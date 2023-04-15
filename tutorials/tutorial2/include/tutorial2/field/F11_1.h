// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"Field 11_1"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/field/F11_1Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"Field 11_1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class F11_1 : public
    comms::field::IntValue<
        tutorial2::field::FieldBase<>,
        std::uint8_t,
        TExtraOpts...
    >
{
    using Base =
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint8_t,
            TExtraOpts...
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return tutorial2::field::F11_1Common::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::F11_1Common::name();
    }
};

} // namespace field

} // namespace tutorial2
