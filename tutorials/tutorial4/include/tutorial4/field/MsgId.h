// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial4/field/FieldBase.h"
#include "tutorial4/field/MsgIdCommon.h"
#include "tutorial4/options/DefaultOptions.h"

namespace tutorial4
{

namespace field
{


/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref tutorial4::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial4::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial4::field::FieldBase<>,
        tutorial4::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 2>
    >
{
    using Base =
        comms::field::EnumValue<
            tutorial4::field::FieldBase<>,
            tutorial4::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 2>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;
    
    /// @brief Single value name info entry.
    using ValueNameInfo = tutorial4::field::MsgIdCommon::ValueNameInfo;
    
    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref tutorial4::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = tutorial4::field::MsgIdCommon::ValueNamesMapInfo;
    
    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial4::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return tutorial4::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }
    
    /// @brief Retrieve map of enum value names.
    /// @see @ref tutorial4::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return tutorial4::field::MsgIdCommon::valueNamesMap();
    }
    
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial4::field::MsgIdCommon::name();
    }
    

};


} // namespace field

} // namespace tutorial4

