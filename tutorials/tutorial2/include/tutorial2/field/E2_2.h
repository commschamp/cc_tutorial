// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of <b>"E2_2"</b> field.

#pragma once

#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial2/field/E2_2Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"E2_2"</b> field.
/// @see @ref tutorial2::field::E2_2Common::ValueType
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class E2_2 : public
    comms::field::EnumValue<
        tutorial2::field::FieldBase<>,
        tutorial2::field::E2_2Common::ValueType,
        TExtraOpts...,
        comms::option::def::DefaultNumValue<100>,
        comms::option::def::ValidNumValue<0>,
        comms::option::def::ValidNumValue<100>,
        comms::option::def::ValidNumValue<271>
    >
{
    using Base =
        comms::field::EnumValue<
            tutorial2::field::FieldBase<>,
            tutorial2::field::E2_2Common::ValueType,
            TExtraOpts...,
            comms::option::def::DefaultNumValue<100>,
            comms::option::def::ValidNumValue<0>,
            comms::option::def::ValidNumValue<100>,
            comms::option::def::ValidNumValue<271>
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single value name info entry.
    using ValueNameInfo = tutorial2::field::E2_2Common::ValueNameInfo;

    /// @brief Type returned from @ref valueNamesMap() member function.
    /// @see @ref tutorial2::field::E2_2Common::ValueNamesMapInfo.
    using ValueNamesMapInfo = tutorial2::field::E2_2Common::ValueNamesMapInfo;

    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial2::field::E2_2Common::valueName().
    static const char* valueName(ValueType val)
    {
        return tutorial2::field::E2_2Common::valueName(val);
    }

    /// @brief Retrieve name of the enum value.
    /// @see @ref tutorial2::field::E2_2Common::valueName().
    static const char* valueNameOf(ValueType val)
    {
        return tutorial2::field::E2_2Common::valueName(val);
    }

    /// @brief Retrieve name of the @b current value
    const char* valueName() const
    {
        return valueName(Base::getValue());
    }

    /// @brief Retrieve map of enum value names.
    /// @see @ref tutorial2::field::E2_2Common::valueNamesMap().
    static ValueNamesMapInfo valueNamesMap()
    {
        return tutorial2::field::E2_2Common::valueNamesMap();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::E2_2Common::name();
    }
};

} // namespace field

} // namespace tutorial2
