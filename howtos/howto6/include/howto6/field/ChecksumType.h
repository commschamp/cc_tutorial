// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of <b>"ChecksumType"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "howto6/field/ChecksumTypeCommon.h"
#include "howto6/field/FieldBase.h"
#include "howto6/options/DefaultOptions.h"

namespace howto6
{

namespace field
{

/// @brief Definition of <b>"ChecksumType"</b> field.
/// @see @ref howto6::field::ChecksumTypeCommon::ValueType
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto6::options::DefaultOptions, typename... TExtraOpts>
class ChecksumType : public
    comms::field::EnumValue<
        howto6::field::FieldBase<>,
        howto6::field::ChecksumTypeCommon::ValueType,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<0, 2>
    >
{
    using Base =
        comms::field::EnumValue<
            howto6::field::FieldBase<>,
            howto6::field::ChecksumTypeCommon::ValueType,
            TExtraOpts...,
            comms::option::def::ValidNumValueRange<0, 2>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single value name info entry.
    using ValueNameInfo = howto6::field::ChecksumTypeCommon::ValueNameInfo;

    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref howto6::field::ChecksumTypeCommon::ValueNamesMapInfo.
    using ValueNamesMapInfo = howto6::field::ChecksumTypeCommon::ValueNamesMapInfo;

    /// @brief Retrieve name of the enum value.
    /// @see @ref howto6::field::ChecksumTypeCommon::valueName().
    static const char* valueName(ValueType val)
    {
        return howto6::field::ChecksumTypeCommon::valueName(val);
    }

    /// @brief Retrieve name of the enum value.
    /// @see @ref howto6::field::ChecksumTypeCommon::valueName().
    static const char* valueNameOf(ValueType val)
    {
        return howto6::field::ChecksumTypeCommon::valueName(val);
    }

    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }

    /// @brief Retrieve map of enum value names.
    /// @see @ref howto6::field::ChecksumTypeCommon::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return howto6::field::ChecksumTypeCommon::valueNamesMap();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto6::field::ChecksumTypeCommon::name();
    }
};

} // namespace field

} // namespace howto6
