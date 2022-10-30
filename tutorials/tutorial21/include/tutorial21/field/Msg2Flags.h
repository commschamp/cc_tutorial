// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of <b>"Msg2Flags"</b> field.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/Bitfield.h"
#include "comms/field/EnumValue.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial21/field/FieldBase.h"
#include "tutorial21/field/Msg2FlagsCommon.h"
#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref Msg2Flags field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial21::options::DefaultOptions>
struct Msg2FlagsMembers
{
    /// @brief Definition of <b>"EnumMem"</b> field.
    /// @see @ref tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::ValueType
    class EnumMem : public
        comms::field::EnumValue<
            tutorial21::field::FieldBase<>,
            tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::ValueType,
            comms::option::def::FixedBitLength<2U>,
            comms::option::def::ValidNumValueRange<0, 3>
        >
    {
        using Base =
            comms::field::EnumValue<
                tutorial21::field::FieldBase<>,
                tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::ValueType,
                comms::option::def::FixedBitLength<2U>,
                comms::option::def::ValidNumValueRange<0, 3>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Single value name info entry.
        using ValueNameInfo = tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::ValueNameInfo;

        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @see @ref tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::ValueNamesMapInfo.
        using ValueNamesMapInfo = tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::ValueNamesMapInfo;

        /// @brief Retrieve name of the enum value.
        /// @see @ref tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::valueName().
        static const char* valueName(ValueType val)
        {
            return tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::valueName(val);
        }

        /// @brief Retrieve name of the enum value.
        /// @see @ref tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::valueName().
        static const char* valueNameOf(ValueType val)
        {
            return tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::valueName(val);
        }

        /// @brief Retrieve name of the @b current value
        const char* valueName() const
        {
            return valueName(Base::getValue());
        }

        /// @brief Retrieve map of enum value names.
        /// @see @ref tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::valueNamesMap().
        static ValueNamesMapInfo valueNamesMap()
        {
            return tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::valueNamesMap();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial21::field::Msg2FlagsMembersCommon::EnumMemCommon::name();
        }
    };

    /// @brief Definition of <b>"IntMem"</b> field.
    class IntMem : public
        comms::field::IntValue<
            tutorial21::field::FieldBase<>,
            std::uint8_t,
            comms::option::def::FixedBitLength<6U>
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial21::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FixedBitLength<6U>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial21::field::Msg2FlagsMembersCommon::IntMemCommon::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial21::field::Msg2FlagsMembersCommon::IntMemCommon::name();
        }
    };

    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           EnumMem,
           IntMem
        >;
};

/// @brief Definition of <b>"Msg2Flags"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial21::options::DefaultOptions, typename... TExtraOpts>
class Msg2Flags : public
    comms::field::Bitfield<
        tutorial21::field::FieldBase<>,
        typename Msg2FlagsMembers<TOpt>::All,
        TExtraOpts...
    >
{
    using Base =
        comms::field::Bitfield<
            tutorial21::field::FieldBase<>,
            typename Msg2FlagsMembers<TOpt>::All,
            TExtraOpts...
        >;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
    ///     related to @b comms::field::Bitfield class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and access functions are:
    ///     @li @b FieldIdx_enumMem index, @b Field_enumMem type and @b field_enumMem() access function -
    ///         for tutorial21::field::Msg2FlagsMembers::EnumMem member field.
    ///     @li @b FieldIdx_intMem index, @b Field_intMem type and @b field_intMem() access function -
    ///         for tutorial21::field::Msg2FlagsMembers::IntMem member field.
    COMMS_FIELD_MEMBERS_NAMES(
        enumMem,
        intMem
    );

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial21::field::Msg2FlagsCommon::name();
    }
};

} // namespace field

} // namespace tutorial21
