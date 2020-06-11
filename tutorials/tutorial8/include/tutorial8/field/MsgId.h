// Generated by commsdsl2comms v3.4.1

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include <cstdint>
#include <type_traits>
#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial8/MsgId.h"
#include "tutorial8/field/FieldBase.h"
#include "tutorial8/field/MsgIdCommon.h"
#include "tutorial8/options/DefaultOptions.h"

namespace tutorial8
{

namespace field
{

/// @brief Definition of <b>"MsgId"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial8::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial8::field::FieldBase<>,
        tutorial8::MsgId,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 3>
    >
{
    using Base = 
        comms::field::EnumValue<
            tutorial8::field::FieldBase<>,
            tutorial8::MsgId,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 3>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial8::field::MsgIdCommon::name();
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(ValueType val)
    {
        return tutorial8::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::value());
    }
    
};

} // namespace field

} // namespace tutorial8


