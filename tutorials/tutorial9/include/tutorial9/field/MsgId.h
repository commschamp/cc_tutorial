// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial9/field/FieldBase.h"
#include "tutorial9/field/MsgIdCommon.h"
#include "tutorial9/options/DefaultOptions.h"

namespace tutorial9
{

namespace field
{


/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref tutorial9::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial9::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial9::field::FieldBase<>,
        tutorial9::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 4>
    >
{
    using Base =
        comms::field::EnumValue<
            tutorial9::field::FieldBase<>,
            tutorial9::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 4>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;
    
    /// @brief Single value name info entry.
    using ValueNameInfo = tutorial9::field::MsgIdCommon::ValueNameInfo;
    
    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref tutorial9::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = tutorial9::field::MsgIdCommon::ValueNamesMapInfo;
    
    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial9::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return tutorial9::field::MsgIdCommon::valueName(val);
    }
    
    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }
    
    /// @brief Retrieve map of enum value names.
    /// @see @ref tutorial9::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return tutorial9::field::MsgIdCommon::valueNamesMap();
    }
    
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial9::field::MsgIdCommon::name();
    }
    

};


} // namespace field

} // namespace tutorial9

