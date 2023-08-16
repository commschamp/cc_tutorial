// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of <b>"SizeField"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "howto9/field/FieldBase.h"
#include "howto9/field/SizeFieldCommon.h"
#include "howto9/options/DefaultOptions.h"

namespace howto9
{

namespace field
{

/// @brief Definition of <b>"SizeField"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto9::options::DefaultOptions, typename... TExtraOpts>
class SizeField : public
    comms::field::IntValue<
        howto9::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...
    >
{
    using Base =
        comms::field::IntValue<
            howto9::field::FieldBase<>,
            std::uint16_t,
            TExtraOpts...
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return howto9::field::SizeFieldCommon::hasSpecials();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto9::field::SizeFieldCommon::name();
    }
};

} // namespace field

} // namespace howto9
