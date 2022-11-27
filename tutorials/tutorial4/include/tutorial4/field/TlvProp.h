// Generated by commsdsl2comms v5.1.3

/// @file
/// @brief Contains definition of <b>"TlvProp"</b> field.

#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <tuple>
#include "comms/Assert.h"
#include "comms/CompileControl.h"
#include "comms/field/ArrayList.h"
#include "comms/field/Bundle.h"
#include "comms/field/FloatValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/field/Variant.h"
#include "comms/options.h"
#include "tutorial4/field/FieldBase.h"
#include "tutorial4/field/TlvPropCommon.h"
#include "tutorial4/options/DefaultOptions.h"

namespace tutorial4
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref TlvProp field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial4::options::DefaultOptions>
struct TlvPropMembers
{
    /// @brief Scope for all the member fields of
    ///     @ref Prop4 field.
    struct Prop4Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<10>,
                comms::option::def::ValidNumValue<10>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::DefaultNumValue<10>,
                    comms::option::def::ValidNumValue<10>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(10);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint32_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint32_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::ValCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Length,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop4"</b> field.
    class Prop4 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop4Members::All,
            comms::option::def::RemLengthMemberField<1U>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop4Members::All,
                comms::option::def::RemLengthMemberField<1U>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop4Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop4Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop4Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::TlvPropMembersCommon::Prop4Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop5 field.
    struct Prop5Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<15>,
                comms::option::def::ValidNumValue<15>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::DefaultNumValue<15>,
                    comms::option::def::ValidNumValue<15>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(15);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::FloatValue<
                tutorial4::field::FieldBase<>,
                double
            >
        {
            using Base =
                comms::field::FloatValue<
                    tutorial4::field::FieldBase<>,
                    double
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Generated default constructor.
            Val()
            {
                Base::setValue(std::numeric_limits<ValueType>::infinity());
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::ValCommon::hasSpecials();
            }

            /// @brief Requested number of digits after decimal point when value
            ///     is displayed.
            static constexpr unsigned displayDecimals()
            {
                return 0U;
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Length,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop5"</b> field.
    class Prop5 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop5Members::All,
            comms::option::def::RemLengthMemberField<1U>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop5Members::All,
                comms::option::def::RemLengthMemberField<1U>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop5Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop5Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop5Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::TlvPropMembersCommon::Prop5Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop6 field.
    struct Prop6Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<25>,
                comms::option::def::ValidNumValue<25>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::DefaultNumValue<25>,
                    comms::option::def::ValidNumValue<25>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(25);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::String<
                tutorial4::field::FieldBase<>,
                typename TOpt::field::TlvPropMembers::Prop6Members::Val
            >
        {
            using Base =
                comms::field::String<
                    tutorial4::field::FieldBase<>,
                    typename TOpt::field::TlvPropMembers::Prop6Members::Val
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Length,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop6"</b> field.
    class Prop6 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop6Members::All,
            comms::option::def::RemLengthMemberField<1U>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop6Members::All,
                comms::option::def::RemLengthMemberField<1U>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop6Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop6Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop6Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::TlvPropMembersCommon::Prop6Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop7 field.
    struct Prop7Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<30>,
                comms::option::def::ValidNumValue<30>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::DefaultNumValue<30>,
                    comms::option::def::ValidNumValue<30>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop7MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop7MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(30);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop7MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop7MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint64_t,
                comms::option::def::AvailableLengthLimit
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint64_t,
                    comms::option::def::AvailableLengthLimit
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop7MembersCommon::ValCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop7MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Length,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop7"</b> field.
    class Prop7 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop7Members::All,
            comms::option::def::RemLengthMemberField<1U>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop7Members::All,
                comms::option::def::RemLengthMemberField<1U>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop7Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop7Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::TlvPropMembers::Prop7Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::TlvPropMembersCommon::Prop7Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Any field.
    struct AnyMembers
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::AnyMembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::AnyMembersCommon::KeyCommon::name();
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::TlvPropMembersCommon::AnyMembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::AnyMembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::ArrayList<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                typename TOpt::field::TlvPropMembers::AnyMembers::Val
            >
        {
            using Base =
                comms::field::ArrayList<
                    tutorial4::field::FieldBase<>,
                    std::uint8_t,
                    typename TOpt::field::TlvPropMembers::AnyMembers::Val
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::AnyMembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Length,
               Val
            >;
    };

    /// @brief Definition of <b>"Any"</b> field.
    class Any : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename AnyMembers::All,
            comms::option::def::RemLengthMemberField<1U>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename AnyMembers::All,
                comms::option::def::RemLengthMemberField<1U>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for tutorial4::field::TlvPropMembers::AnyMembers::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for tutorial4::field::TlvPropMembers::AnyMembers::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::TlvPropMembers::AnyMembers::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::TlvPropMembersCommon::AnyCommon::name();
        }
    };

    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           Prop4,
           Prop5,
           Prop6,
           Prop7,
           Any
        >;
};

/// @brief Definition of <b>"TlvProp"</b> field.
/// @details
///     Type-Length-Value Property
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial4::options::DefaultOptions, typename... TExtraOpts>
class TlvProp : public
    comms::field::Variant<
        tutorial4::field::FieldBase<>,
        typename TlvPropMembers<TOpt>::All,
        TExtraOpts...,
        comms::option::def::HasCustomRead
    >
{
    using Base =
        comms::field::Variant<
            tutorial4::field::FieldBase<>,
            typename TlvPropMembers<TOpt>::All,
            TExtraOpts...,
            comms::option::def::HasCustomRead
        >;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_VARIANT_MEMBERS_NAMES macro
    ///     related to @b comms::field::Variant class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and access functions are:
    ///     @li @b FieldIdx_prop4 index, @b Field_prop4 type,
    ///         @b initField_prop4() and @b accessField_prop4() access functions -
    ///         for tutorial4::field::TlvPropMembers::Prop4 member field.
    ///     @li @b FieldIdx_prop5 index, @b Field_prop5 type,
    ///         @b initField_prop5() and @b accessField_prop5() access functions -
    ///         for tutorial4::field::TlvPropMembers::Prop5 member field.
    ///     @li @b FieldIdx_prop6 index, @b Field_prop6 type,
    ///         @b initField_prop6() and @b accessField_prop6() access functions -
    ///         for tutorial4::field::TlvPropMembers::Prop6 member field.
    ///     @li @b FieldIdx_prop7 index, @b Field_prop7 type,
    ///         @b initField_prop7() and @b accessField_prop7() access functions -
    ///         for tutorial4::field::TlvPropMembers::Prop7 member field.
    ///     @li @b FieldIdx_any index, @b Field_any type,
    ///         @b initField_any() and @b accessField_any() access functions -
    ///         for tutorial4::field::TlvPropMembers::Any member field.
    COMMS_VARIANT_MEMBERS_NAMES(
        prop4,
        prop5,
        prop6,
        prop7,
        any
    );

    /// @brief Optimized currFieldExec functionality.
    /// @details Replaces the currFieldExec() member function defined
    ///    by @b comms::field::Variant.
    template <typename TFunc>
    void currFieldExec(TFunc&& func) 
    {
        switch (Base::currentField()) {
        case FieldIdx_prop4:
            memFieldDispatch<FieldIdx_prop4>(accessField_prop4(), std::forward<TFunc>(func));
            break;
        case FieldIdx_prop5:
            memFieldDispatch<FieldIdx_prop5>(accessField_prop5(), std::forward<TFunc>(func));
            break;
        case FieldIdx_prop6:
            memFieldDispatch<FieldIdx_prop6>(accessField_prop6(), std::forward<TFunc>(func));
            break;
        case FieldIdx_prop7:
            memFieldDispatch<FieldIdx_prop7>(accessField_prop7(), std::forward<TFunc>(func));
            break;
        case FieldIdx_any:
            memFieldDispatch<FieldIdx_any>(accessField_any(), std::forward<TFunc>(func));
            break;
        default:
            static constexpr bool Invalid_field_execution = false;
            static_cast<void>(Invalid_field_execution);
            COMMS_ASSERT(Invalid_field_execution);
            break;
        }
    }

    /// @brief Optimized currFieldExec functionality (const variant).
    /// @details Replaces the currFieldExec() member function defined
    ///    by @b comms::field::Variant.
    template <typename TFunc>
    void currFieldExec(TFunc&& func) const
    {
        switch (Base::currentField()) {
        case FieldIdx_prop4:
            memFieldDispatch<FieldIdx_prop4>(accessField_prop4(), std::forward<TFunc>(func));
            break;
        case FieldIdx_prop5:
            memFieldDispatch<FieldIdx_prop5>(accessField_prop5(), std::forward<TFunc>(func));
            break;
        case FieldIdx_prop6:
            memFieldDispatch<FieldIdx_prop6>(accessField_prop6(), std::forward<TFunc>(func));
            break;
        case FieldIdx_prop7:
            memFieldDispatch<FieldIdx_prop7>(accessField_prop7(), std::forward<TFunc>(func));
            break;
        case FieldIdx_any:
            memFieldDispatch<FieldIdx_any>(accessField_any(), std::forward<TFunc>(func));
            break;
        default:
            static constexpr bool Invalid_field_execution = false;
            static_cast<void>(Invalid_field_execution);
            COMMS_ASSERT(Invalid_field_execution);
            break;
        }
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial4::field::TlvPropCommon::name();
    }

    COMMS_MSVC_WARNING_PUSH
    COMMS_MSVC_WARNING_DISABLE(4702)
    /// @brief Generated read functionality.
    template <typename TIter>
    comms::ErrorStatus read(TIter& iter, std::size_t len)
    {
        using CommonKeyField=
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>
            >;
        CommonKeyField commonKeyField;

        auto origIter = iter;
        auto es = commonKeyField.read(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto consumedLen = static_cast<std::size_t>(std::distance(origIter, iter));
        COMMS_ASSERT(consumedLen <= len);
        len -= consumedLen;

        switch (commonKeyField.getValue()) {
        case 10U /* 0x0AU */:
            {
                auto& field_prop4 = initField_prop4();
                COMMS_ASSERT(field_prop4.field_key().getValue() == commonKeyField.getValue());
                return field_prop4.template readFrom<1>(iter, len);
            }
        case 15U /* 0x0FU */:
            {
                auto& field_prop5 = initField_prop5();
                COMMS_ASSERT(field_prop5.field_key().getValue() == commonKeyField.getValue());
                return field_prop5.template readFrom<1>(iter, len);
            }
        case 25U /* 0x19U */:
            {
                auto& field_prop6 = initField_prop6();
                COMMS_ASSERT(field_prop6.field_key().getValue() == commonKeyField.getValue());
                return field_prop6.template readFrom<1>(iter, len);
            }
        case 30U /* 0x1EU */:
            {
                auto& field_prop7 = initField_prop7();
                COMMS_ASSERT(field_prop7.field_key().getValue() == commonKeyField.getValue());
                return field_prop7.template readFrom<1>(iter, len);
            }
        default:
            initField_any().field_key().setValue(commonKeyField.getValue());
            return accessField_any().template readFrom<1>(iter, len);
        };

        return comms::ErrorStatus::InvalidMsgData;
    }
    COMMS_MSVC_WARNING_POP

private:
    template <std::size_t TIdx, typename TField, typename TFunc>
    static void memFieldDispatch(TField&& f, TFunc&& func)
    {
        #ifdef _MSC_VER
            func.operator()<TIdx>(std::forward<TField>(f)); // VS compiler
        #else // #ifdef _MSC_VER
            func.template operator()<TIdx>(std::forward<TField>(f)); // All other compilers
        #endif // #ifdef _MSC_VER
    }
};

} // namespace field

} // namespace tutorial4
