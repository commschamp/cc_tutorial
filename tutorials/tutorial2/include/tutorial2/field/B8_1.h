// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of <b>"B8_1"</b> field.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/Bundle.h"
#include "comms/field/EnumValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/field/B8_1Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref B8_1 field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct B8_1Members
{
    /// @brief Definition of <b>"M1"</b> field.
    class M1 : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial2::field::B8_1MembersCommon::M1Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::B8_1MembersCommon::M1Common::name();
        }
    };

    /// @brief Definition of <b>"M2"</b> field.
    /// @see @ref tutorial2::field::B8_1MembersCommon::M2Common::ValueType
    class M2 : public
        comms::field::EnumValue<
            tutorial2::field::FieldBase<>,
            tutorial2::field::B8_1MembersCommon::M2Common::ValueType,
            comms::option::def::ValidNumValueRange<0, 1>
        >
    {
        using Base =
            comms::field::EnumValue<
                tutorial2::field::FieldBase<>,
                tutorial2::field::B8_1MembersCommon::M2Common::ValueType,
                comms::option::def::ValidNumValueRange<0, 1>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Single value name info entry.
        using ValueNameInfo = tutorial2::field::B8_1MembersCommon::M2Common::ValueNameInfo;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @see @ref tutorial2::field::B8_1MembersCommon::M2Common::ValueNamesMapInfo.
        using ValueNamesMapInfo = tutorial2::field::B8_1MembersCommon::M2Common::ValueNamesMapInfo;

        /// @brief Retrieve name of the enum value.
        /// @see @ref tutorial2::field::B8_1MembersCommon::M2Common::valueName().
        static const char* valueName(ValueType val)
        {
            return tutorial2::field::B8_1MembersCommon::M2Common::valueName(val);
        }

        /// @brief Retrieve name of the enum value.
        /// @see @ref tutorial2::field::B8_1MembersCommon::M2Common::valueName().
        static const char* valueNameOf(ValueType val)
        {
            return tutorial2::field::B8_1MembersCommon::M2Common::valueName(val);
        }

        /// @brief Retrieve name of the @b current value
        const char* valueName() const
        {
            return valueName(Base::getValue());
        }

        /// @brief Retrieve map of enum value names.
        /// @see @ref tutorial2::field::B8_1MembersCommon::M2Common::valueNamesMap().
        static ValueNamesMapInfo valueNamesMap()
        {
            return tutorial2::field::B8_1MembersCommon::M2Common::valueNamesMap();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::B8_1MembersCommon::M2Common::name();
        }
    };

    /// @brief Definition of <b>"M3"</b> field.
    class M3 : public
        comms::field::String<
            tutorial2::field::FieldBase<>,
            typename TOpt::field::B8_1Members::M3,
            comms::option::def::SequenceFixedSize<3U>
        >
    {
        using Base =
            comms::field::String<
                tutorial2::field::FieldBase<>,
                typename TOpt::field::B8_1Members::M3,
                comms::option::def::SequenceFixedSize<3U>
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::B8_1MembersCommon::M3Common::name();
        }
    };

    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           M1,
           M2,
           M3
        >;
};

/// @brief Definition of <b>"B8_1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class B8_1 : public
    comms::field::Bundle<
        tutorial2::field::FieldBase<>,
        typename B8_1Members<TOpt>::All,
        TExtraOpts...,
        comms::option::def::HasVersionDependentMembers<false>
    >
{
    using Base =
        comms::field::Bundle<
            tutorial2::field::FieldBase<>,
            typename B8_1Members<TOpt>::All,
            TExtraOpts...,
            comms::option::def::HasVersionDependentMembers<false>
        >;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
    ///     related to @b comms::field::Bundle class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and access functions are:
    ///     @li @b FieldIdx_m1 index, @b Field_m1 type and @b field_m1() access function -
    ///         for tutorial2::field::B8_1Members::M1 member field.
    ///     @li @b FieldIdx_m2 index, @b Field_m2 type and @b field_m2() access function -
    ///         for tutorial2::field::B8_1Members::M2 member field.
    ///     @li @b FieldIdx_m3 index, @b Field_m3 type and @b field_m3() access function -
    ///         for tutorial2::field::B8_1Members::M3 member field.
    COMMS_FIELD_MEMBERS_NAMES(
        m1,
        m2,
        m3
    );

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::B8_1Common::name();
    }
};

} // namespace field

} // namespace tutorial2
