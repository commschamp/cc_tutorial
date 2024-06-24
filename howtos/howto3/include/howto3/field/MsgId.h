// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "howto3/field/FieldBase.h"
#include "howto3/field/MsgIdCommon.h"
#include "howto3/options/DefaultOptions.h"

namespace howto3
{

namespace field
{

/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref howto3::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto3::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        howto3::field::FieldBase<>,
        howto3::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 4>
    >
{
    using Base =
        comms::field::EnumValue<
            howto3::field::FieldBase<>,
            howto3::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 4>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single value name info entry.
    using ValueNameInfo = howto3::field::MsgIdCommon::ValueNameInfo;

    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref howto3::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = howto3::field::MsgIdCommon::ValueNamesMapInfo;

    /// @brief Retrieve name of the enum value.
    /// @see @ref howto3::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return howto3::field::MsgIdCommon::valueName(val);
    }

    /// @brief Retrieve name of the enum value.
    /// @see @ref howto3::field::MsgIdCommon::valueName().
    static const char* valueNameOf(ValueType val)
    {
        return howto3::field::MsgIdCommon::valueName(val);
    }

    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }

    /// @brief Retrieve map of enum value names.
    /// @see @ref howto3::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return howto3::field::MsgIdCommon::valueNamesMap();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto3::field::MsgIdCommon::name();
    }
};

} // namespace field

} // namespace howto3
