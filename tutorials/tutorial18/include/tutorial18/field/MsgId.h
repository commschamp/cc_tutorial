// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"ID"</b> field.

#pragma once

#include <cstdint>
#include <type_traits>
#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial18/MsgId.h"
#include "tutorial18/field/FieldBase.h"
#include "tutorial18/field/MsgIdCommon.h"
#include "tutorial18/options/DefaultOptions.h"

namespace tutorial18
{

namespace field
{

/// @brief Definition of <b>"ID"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial18::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial18::field::FieldBase<>,
        tutorial18::MsgId,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 2>
    >
{
    using Base = 
        comms::field::EnumValue<
            tutorial18::field::FieldBase<>,
            tutorial18::MsgId,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 2>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial18::field::MsgIdCommon::name();
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(ValueType val)
    {
        return tutorial18::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::value());
    }
    
};

} // namespace field

} // namespace tutorial18


