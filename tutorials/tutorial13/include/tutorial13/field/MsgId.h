// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include <cstdint>
#include <type_traits>
#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial13/MsgId.h"
#include "tutorial13/field/FieldBase.h"
#include "tutorial13/field/MsgIdCommon.h"
#include "tutorial13/options/DefaultOptions.h"

namespace tutorial13
{

namespace field
{

/// @brief Definition of <b>"MsgId"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial13::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial13::field::FieldBase<>,
        tutorial13::MsgId,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 2>
    >
{
    using Base = 
        comms::field::EnumValue<
            tutorial13::field::FieldBase<>,
            tutorial13::MsgId,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 2>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial13::field::MsgIdCommon::name();
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(ValueType val)
    {
        return tutorial13::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::value());
    }
    
};

} // namespace field

} // namespace tutorial13


