// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of <b>"L10_3"</b> field.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/ArrayList.h"
#include "comms/field/Bundle.h"
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/L10_3Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref L10_3 field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct L10_3Members
{
    /// @brief Scope for all the member fields of
    ///     @ref Element field.
    struct ElementMembers
    {
        /// @brief Definition of <b>"M1"</b> field.
        class M1 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial2::field::L10_3MembersCommon::ElementMembersCommon::M1Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::field::L10_3MembersCommon::ElementMembersCommon::M1Common::name();
            }
        };

        /// @brief Definition of <b>"M2"</b> field.
        class M2 : public
            comms::field::String<
                tutorial2::field::FieldBase<>,
                typename TOpt::field::L10_3Members::ElementMembers::M2,
                comms::option::def::SequenceFixedSize<3U>
            >
        {
            using Base =
                comms::field::String<
                    tutorial2::field::FieldBase<>,
                    typename TOpt::field::L10_3Members::ElementMembers::M2,
                    comms::option::def::SequenceFixedSize<3U>
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::field::L10_3MembersCommon::ElementMembersCommon::M2Common::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               M1,
               M2
            >;
    };

    /// @brief Definition of <b>"Element"</b> field.
    class Element : public
        comms::field::Bundle<
            tutorial2::field::FieldBase<>,
            typename ElementMembers::All,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial2::field::FieldBase<>,
                typename ElementMembers::All,
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
        ///         for tutorial2::field::L10_3Members::ElementMembers::M1 member field.
        ///     @li @b FieldIdx_m2 index, @b Field_m2 type and @b field_m2() access function -
        ///         for tutorial2::field::L10_3Members::ElementMembers::M2 member field.
        COMMS_FIELD_MEMBERS_NAMES(
            m1,
            m2
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_3MembersCommon::ElementCommon::name();
        }
    };

    /// @brief Definition of <b>"Length"</b> field.
    class Length : public
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
            return tutorial2::field::L10_3MembersCommon::LengthCommon::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_3MembersCommon::LengthCommon::name();
        }
    };
};

/// @brief Definition of <b>"L10_3"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class L10_3 : public
    comms::field::ArrayList<
        tutorial2::field::FieldBase<>,
        typename L10_3Members<TOpt>::Element,
        TExtraOpts...,
        typename TOpt::field::L10_3,
        comms::option::def::SequenceSerLengthFieldPrefix<typename L10_3Members<TOpt>::Length>
    >
{
    using Base =
        comms::field::ArrayList<
            tutorial2::field::FieldBase<>,
            typename L10_3Members<TOpt>::Element,
            TExtraOpts...,
            typename TOpt::field::L10_3,
            comms::option::def::SequenceSerLengthFieldPrefix<typename L10_3Members<TOpt>::Length>
        >;
public:
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::L10_3Common::name();
    }
};

} // namespace field

} // namespace tutorial2
