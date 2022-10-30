// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "howto9/field/FieldBase.h"
#include "howto9/field/MsgIdCommon.h"
#include "howto9/options/DefaultOptions.h"

namespace howto9
{

namespace field
{

/// @brief Definition of <b>"MsgId"</b> field.
/// @see @ref howto9::MsgId
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto9::options::DefaultOptions, typename... TExtraOpts>
class MsgId : public
    comms::field::EnumValue<
        howto9::field::FieldBase<>,
        howto9::field::MsgIdCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 3>
    >
{
    using Base =
        comms::field::EnumValue<
            howto9::field::FieldBase<>,
            howto9::field::MsgIdCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<1, 3>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single value name info entry.
    using ValueNameInfo = howto9::field::MsgIdCommon::ValueNameInfo;

    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref howto9::field::MsgIdCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = howto9::field::MsgIdCommon::ValueNamesMapInfo;

    /// @brief Retrieve name of the enum value.
    /// @see @ref howto9::field::MsgIdCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return howto9::field::MsgIdCommon::valueName(val);
    }

    /// @brief Retrieve name of the enum value.
    /// @see @ref howto9::field::MsgIdCommon::valueName().
    static const char* valueNameOf(ValueType val)
    {
        return howto9::field::MsgIdCommon::valueName(val);
    }

    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }

    /// @brief Retrieve map of enum value names.
    /// @see @ref howto9::field::MsgIdCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return howto9::field::MsgIdCommon::valueNamesMap();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto9::field::MsgIdCommon::name();
    }
};

} // namespace field

} // namespace howto9
