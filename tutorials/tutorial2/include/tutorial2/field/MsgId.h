// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/MsgIdCommon.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{


/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref tutorial2::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial2::field::FieldBase<>,
        tutorial2::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 14>
    >
{
    using Base =
        comms::field::EnumValue<
            tutorial2::field::FieldBase<>,
            tutorial2::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 14>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;
    
    /// @brief Single value name info entry.
    using ValueNameInfo = tutorial2::field::MsgIdCommon::ValueNameInfo;
    
    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref tutorial2::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = tutorial2::field::MsgIdCommon::ValueNamesMapInfo;
    
    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial2::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return tutorial2::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::value());
    }
    
    /// @brief Retrieve map of enum value names.
    /// @see @ref tutorial2::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return tutorial2::field::MsgIdCommon::valueNamesMap();
    }
    
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::MsgIdCommon::name();
    }
    

};


} // namespace field

} // namespace tutorial2

