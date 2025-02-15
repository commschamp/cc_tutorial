// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"VersionWithFlags"</b> field.

#pragma once

#include <tuple>
#include "comms/field/Bitfield.h"
#include "comms/options.h"
#include "howto5/field/FieldBase.h"
#include "howto5/field/InterfaceFlags.h"
#include "howto5/field/Version.h"
#include "howto5/field/VersionWithFlagsCommon.h"
#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref VersionWithFlags field.
/// @tparam TOpt Protocol options.
template <typename TOpt = howto5::options::DefaultOptions>
struct VersionWithFlagsMembers
{
    /// @brief Definition of <b>"Version"</b> field.
    using Version =
        howto5::field::Version<
            TOpt,
            comms::option::def::HasName,
            comms::option::def::FixedBitLength<12U>
        >;

    /// @brief Definition of <b>"Flags"</b> field.
    class Flags : public
        howto5::field::InterfaceFlags<
            TOpt,
            comms::option::def::HasName,
            comms::option::def::FixedBitLength<4U>
        >
    {
        using Base =
            howto5::field::InterfaceFlags<
                TOpt,
                comms::option::def::HasName,
                comms::option::def::FixedBitLength<4U>
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::field::VersionWithFlagsMembersCommon::FlagsCommon::name();
        }
    };

    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           Version,
           Flags
        >;
};

/// @brief Definition of <b>"VersionWithFlags"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto5::options::DefaultOptions, typename... TExtraOpts>
class VersionWithFlags : public
    comms::field::Bitfield<
        howto5::field::FieldBase<>,
        typename VersionWithFlagsMembers<TOpt>::All,
        TExtraOpts...,
        comms::option::def::HasName,
        comms::option::def::HasVersionDependentMembers<false>
    >
{
    using Base =
        comms::field::Bitfield<
            howto5::field::FieldBase<>,
            typename VersionWithFlagsMembers<TOpt>::All,
            TExtraOpts...,
            comms::option::def::HasName,
            comms::option::def::HasVersionDependentMembers<false>
        >;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
    ///     related to @b comms::field::Bitfield class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and access functions are:
    ///     @li @b FieldIdx_version index, @b Field_version type and @b field_version() access function -
    ///         for howto5::field::VersionWithFlagsMembers::Version member field.
    ///     @li @b FieldIdx_flags index, @b Field_flags type and @b field_flags() access function -
    ///         for howto5::field::VersionWithFlagsMembers::Flags member field.
    COMMS_FIELD_MEMBERS_NAMES(
        version,
        flags
    );

    /// @brief Name of the field.
    static const char* name()
    {
        return howto5::field::VersionWithFlagsCommon::name();
    }
};

} // namespace field

} // namespace howto5
