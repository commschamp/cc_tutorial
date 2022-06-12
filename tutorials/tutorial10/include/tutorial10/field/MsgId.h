// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial10/field/FieldBase.h"
#include "tutorial10/field/MsgIdCommon.h"
#include "tutorial10/options/DefaultOptions.h"

namespace tutorial10
{

namespace field
{


/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref tutorial10::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial10::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial10::field::FieldBase<>,
        tutorial10::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 5>
    >
{
    using Base =
        comms::field::EnumValue<
            tutorial10::field::FieldBase<>,
            tutorial10::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 5>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;
    
    /// @brief Single value name info entry.
    using ValueNameInfo = tutorial10::field::MsgIdCommon::ValueNameInfo;
    
    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref tutorial10::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = tutorial10::field::MsgIdCommon::ValueNamesMapInfo;
    
    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial10::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return tutorial10::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }
    
    /// @brief Retrieve map of enum value names.
    /// @see @ref tutorial10::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return tutorial10::field::MsgIdCommon::valueNamesMap();
    }
    
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial10::field::MsgIdCommon::name();
    }
    

};


} // namespace field

} // namespace tutorial10

