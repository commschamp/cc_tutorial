// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial21/field/FieldBase.h"
#include "tutorial21/field/MsgIdCommon.h"
#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace field
{

/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref tutorial21::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial21::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        tutorial21::field::FieldBase<>,
        tutorial21::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 3>
    >
{
    using Base =
        comms::field::EnumValue<
            tutorial21::field::FieldBase<>,
            tutorial21::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 3>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single value name info entry.
    using ValueNameInfo = tutorial21::field::MsgIdCommon::ValueNameInfo;

    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref tutorial21::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = tutorial21::field::MsgIdCommon::ValueNamesMapInfo;

    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial21::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return tutorial21::field::MsgIdCommon::valueName(val);
    }

    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial21::field::MsgIdCommon::valueName().
    static const char* valueNameOf(ValueType val)
    {
        return tutorial21::field::MsgIdCommon::valueName(val);
    }

    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }

    /// @brief Retrieve map of enum value names.
    /// @see @ref tutorial21::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return tutorial21::field::MsgIdCommon::valueNamesMap();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial21::field::MsgIdCommon::name();
    }
};

} // namespace field

} // namespace tutorial21
