// Generated by commsdsl2comms v6.2.1

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
#include "howto4/field/FieldBase.h"
#include "howto4/field/TlvPropCommon.h"
#include "howto4/options/DefaultOptions.h"

namespace howto4
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref TlvProp field.
/// @tparam TOpt Protocol options.
template <typename TOpt = howto4::options::DefaultOptions>
struct TlvPropMembers
{
    /// @brief Scope for all the member fields of
    ///     @ref Prop1 field.
    struct Prop1Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::ValidNumValue<0>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::ValidNumValue<0>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop1MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop1MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(0);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop1MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop1MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint32_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint32_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop1MembersCommon::ValCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop1MembersCommon::ValCommon::name();
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

    /// @brief Definition of <b>"Prop1"</b> field.
    class Prop1 : public
        comms::field::Bundle<
            howto4::field::FieldBase<>,
            typename Prop1Members::All,
            comms::option::def::RemLengthMemberField<1U>,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                howto4::field::FieldBase<>,
                typename Prop1Members::All,
                comms::option::def::RemLengthMemberField<1U>,
                comms::option::def::HasVersionDependentMembers<false>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for howto4::field::TlvPropMembers::Prop1Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for howto4::field::TlvPropMembers::Prop1Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for howto4::field::TlvPropMembers::Prop1Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return howto4::field::TlvPropMembersCommon::Prop1Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop2 field.
    struct Prop2Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<2>,
                comms::option::def::ValidNumValue<2>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::DefaultNumValue<2>,
                    comms::option::def::ValidNumValue<2>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop2MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop2MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(2);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop2MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop2MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::FloatValue<
                howto4::field::FieldBase<>,
                double
            >
        {
            using Base =
                comms::field::FloatValue<
                    howto4::field::FieldBase<>,
                    double
                >;
        public:
            /// @brief Default constructor.
            Val()
            {
                Base::setValue(std::numeric_limits<ValueType>::infinity());
            }

            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop2MembersCommon::ValCommon::hasSpecials();
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
                return howto4::field::TlvPropMembersCommon::Prop2MembersCommon::ValCommon::name();
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

    /// @brief Definition of <b>"Prop2"</b> field.
    class Prop2 : public
        comms::field::Bundle<
            howto4::field::FieldBase<>,
            typename Prop2Members::All,
            comms::option::def::RemLengthMemberField<1U>,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                howto4::field::FieldBase<>,
                typename Prop2Members::All,
                comms::option::def::RemLengthMemberField<1U>,
                comms::option::def::HasVersionDependentMembers<false>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for howto4::field::TlvPropMembers::Prop2Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for howto4::field::TlvPropMembers::Prop2Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for howto4::field::TlvPropMembers::Prop2Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return howto4::field::TlvPropMembersCommon::Prop2Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop3 field.
    struct Prop3Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<5>,
                comms::option::def::ValidNumValue<5>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>,
                    comms::option::def::DefaultNumValue<5>,
                    comms::option::def::ValidNumValue<5>,
                    comms::option::def::HasCustomRefresh
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop3MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop3MembersCommon::KeyCommon::name();
            }

            /// @brief Generated refresh functionality.
            bool refresh()
            {
                bool updated = Base::refresh();
                if (Base::valid()) {
                    return updated;
                };
                Base::setValue(5);
                return true;
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::Prop3MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop3MembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::String<
                howto4::field::FieldBase<>,
                typename TOpt::field::TlvPropMembers::Prop3Members::Val
            >
        {
            using Base =
                comms::field::String<
                    howto4::field::FieldBase<>,
                    typename TOpt::field::TlvPropMembers::Prop3Members::Val
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::Prop3MembersCommon::ValCommon::name();
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

    /// @brief Definition of <b>"Prop3"</b> field.
    class Prop3 : public
        comms::field::Bundle<
            howto4::field::FieldBase<>,
            typename Prop3Members::All,
            comms::option::def::RemLengthMemberField<1U>,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                howto4::field::FieldBase<>,
                typename Prop3Members::All,
                comms::option::def::RemLengthMemberField<1U>,
                comms::option::def::HasVersionDependentMembers<false>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for howto4::field::TlvPropMembers::Prop3Members::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for howto4::field::TlvPropMembers::Prop3Members::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for howto4::field::TlvPropMembers::Prop3Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return howto4::field::TlvPropMembersCommon::Prop3Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Any field.
    struct AnyMembers
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::FailOnInvalid<>
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::AnyMembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::AnyMembersCommon::KeyCommon::name();
            }
        };

        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto4::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto4::field::TlvPropMembersCommon::AnyMembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::AnyMembersCommon::LengthCommon::name();
            }
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::ArrayList<
                howto4::field::FieldBase<>,
                std::uint8_t,
                typename TOpt::field::TlvPropMembers::AnyMembers::Val
            >
        {
            using Base =
                comms::field::ArrayList<
                    howto4::field::FieldBase<>,
                    std::uint8_t,
                    typename TOpt::field::TlvPropMembers::AnyMembers::Val
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return howto4::field::TlvPropMembersCommon::AnyMembersCommon::ValCommon::name();
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
            howto4::field::FieldBase<>,
            typename AnyMembers::All,
            comms::option::def::RemLengthMemberField<1U>,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                howto4::field::FieldBase<>,
                typename AnyMembers::All,
                comms::option::def::RemLengthMemberField<1U>,
                comms::option::def::HasVersionDependentMembers<false>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_key index, @b Field_key type and @b field_key() access function -
        ///         for howto4::field::TlvPropMembers::AnyMembers::Key member field.
        ///     @li @b FieldIdx_length index, @b Field_length type and @b field_length() access function -
        ///         for howto4::field::TlvPropMembers::AnyMembers::Length member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for howto4::field::TlvPropMembers::AnyMembers::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            length,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return howto4::field::TlvPropMembersCommon::AnyCommon::name();
        }
    };

    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           Prop1,
           Prop2,
           Prop3,
           Any
        >;
};

/// @brief Definition of <b>"TlvProp"</b> field.
/// @details
///     Type-Length-Value Property
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto4::options::DefaultOptions, typename... TExtraOpts>
class TlvProp : public
    comms::field::Variant<
        howto4::field::FieldBase<>,
        typename TlvPropMembers<TOpt>::All,
        TExtraOpts...,
        comms::option::def::HasCustomRead,
        comms::option::def::HasCustomWrite,
        comms::option::def::HasCustomRefresh,
        comms::option::def::VariantHasCustomResetOnDestruct,
        comms::option::def::HasVersionDependentMembers<false>
    >
{
    using Base =
        comms::field::Variant<
            howto4::field::FieldBase<>,
            typename TlvPropMembers<TOpt>::All,
            TExtraOpts...,
            comms::option::def::HasCustomRead,
            comms::option::def::HasCustomWrite,
            comms::option::def::HasCustomRefresh,
            comms::option::def::VariantHasCustomResetOnDestruct,
            comms::option::def::HasVersionDependentMembers<false>
        >;
public:
    /// @brief Default constructor.
    TlvProp() = default;

    /// @brief Destructor
    ~TlvProp()
    {
        reset();
    }

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_VARIANT_MEMBERS_NAMES macro
    ///     related to @b comms::field::Variant class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and access functions are:
    ///     @li @b FieldIdx_prop1 index, @b Field_prop1 type,
    ///         @b initField_prop1(), @b deinitField_prop1() and @b accessField_prop1() access functions -
    ///         for howto4::field::TlvPropMembers::Prop1 member field.
    ///     @li @b FieldIdx_prop2 index, @b Field_prop2 type,
    ///         @b initField_prop2(), @b deinitField_prop2() and @b accessField_prop2() access functions -
    ///         for howto4::field::TlvPropMembers::Prop2 member field.
    ///     @li @b FieldIdx_prop3 index, @b Field_prop3 type,
    ///         @b initField_prop3(), @b deinitField_prop3() and @b accessField_prop3() access functions -
    ///         for howto4::field::TlvPropMembers::Prop3 member field.
    ///     @li @b FieldIdx_any index, @b Field_any type,
    ///         @b initField_any(), @b deinitField_any() and @b accessField_any() access functions -
    ///         for howto4::field::TlvPropMembers::Any member field.
    COMMS_VARIANT_MEMBERS_NAMES(
        prop1,
        prop2,
        prop3,
        any
    );

    /// @brief Copy constructor.
    TlvProp(const TlvProp& other) :
        Base()
    {
        *this = other;
    }

    /// @brief Move constructor.
    TlvProp(TlvProp&& other) : 
        Base()
    {
        *this = std::move(other);
    }

    /// @brief Copy assignment operator.
    TlvProp& operator=(const TlvProp& other)
    {
        if (this == &other) {
            return *this;
        }

        reset();

        if (!other.currentFieldValid()) {
            return *this;
        }

        switch (other.currentField()) {
            case FieldIdx_prop1: initField_prop1() = other.accessField_prop1(); return *this;
            case FieldIdx_prop2: initField_prop2() = other.accessField_prop2(); return *this;
            case FieldIdx_prop3: initField_prop3() = other.accessField_prop3(); return *this;
            case FieldIdx_any: initField_any() = other.accessField_any(); return *this;
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return *this;
    }

    /// @brief Move assignement operator.
    TlvProp& operator=(TlvProp&& other)
    {    if (this == &other) {
            return *this;
        }

        reset();

        if (!other.currentFieldValid()) {
            return *this;
        }

        switch (other.currentField()) {
            case FieldIdx_prop1: initField_prop1() = std::move(other.accessField_prop1()); return *this;
            case FieldIdx_prop2: initField_prop2() = std::move(other.accessField_prop2()); return *this;
            case FieldIdx_prop3: initField_prop3() = std::move(other.accessField_prop3()); return *this;
            case FieldIdx_any: initField_any() = std::move(other.accessField_any()); return *this;
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return *this;
    }

    /// @brief Equality comparison operator.
    bool operator==(const TlvProp& other) const
    {
        if (this == &other) {
            return true;
        }

        if (Base::currentFieldValid() != other.currentFieldValid()) {
            return false;
        }

        if (!Base::currentFieldValid()) {

            return true;
        }

        if (Base::currentField() != other.currentField()) {

            return false;
        }

        switch(Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1() == other.accessField_prop1();
            case FieldIdx_prop2: return accessField_prop2() == other.accessField_prop2();
            case FieldIdx_prop3: return accessField_prop3() == other.accessField_prop3();
            case FieldIdx_any: return accessField_any() == other.accessField_any();
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return false;
    }

    /// @brief Inequality comparison operator.
    bool operator!=(const TlvProp& other) const
    {
        return !(*this == other);
    }

    /// @brief Order comparison operator.
    bool operator<(const TlvProp& other) const
    {
        if (!Base::currentFieldValid()) {
            return (!other.currentFieldValid());
        }

        if (!other.currentFieldValid()) {
            return false;
        }

        if (Base::currentField() < other.currentField()) {
            return true;
        }

        if (Base::currentField() != other.currentField()) {
            return false;
        }

        if (this == &other) {
            return false;
        }
        switch(Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1() < other.accessField_prop1();
            case FieldIdx_prop2: return accessField_prop2() < other.accessField_prop2();
            case FieldIdx_prop3: return accessField_prop3() < other.accessField_prop3();
            case FieldIdx_any: return accessField_any() < other.accessField_any();
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return false;
    }

    /// @brief Optimized currentFieldExec functionality.
    /// @details Replaces the currentFieldExec() member function defined
    ///    by @b comms::field::Variant.
    template <typename TFunc>
    void currentFieldExec(TFunc&& func) 
    {
        switch (Base::currentField()) {
            case FieldIdx_prop1:
                memFieldDispatch<FieldIdx_prop1>(accessField_prop1(), std::forward<TFunc>(func));
                break;
            case FieldIdx_prop2:
                memFieldDispatch<FieldIdx_prop2>(accessField_prop2(), std::forward<TFunc>(func));
                break;
            case FieldIdx_prop3:
                memFieldDispatch<FieldIdx_prop3>(accessField_prop3(), std::forward<TFunc>(func));
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

    /// @brief The same as currentFieldExec() 
    /// @details Generated for backward comatibility, can be removed in the future.
    template <typename TFunc>
    void currFieldExec(TFunc&& func) 
    {
        currentFieldExec(std::forward<TFunc>(func));
    }

    /// @brief Optimized currentFieldExec functionality (const variant).
    /// @details Replaces the currentFieldExec() member function defined
    ///    by @b comms::field::Variant.
    template <typename TFunc>
    void currentFieldExec(TFunc&& func) const
    {
        switch (Base::currentField()) {
            case FieldIdx_prop1:
                memFieldDispatch<FieldIdx_prop1>(accessField_prop1(), std::forward<TFunc>(func));
                break;
            case FieldIdx_prop2:
                memFieldDispatch<FieldIdx_prop2>(accessField_prop2(), std::forward<TFunc>(func));
                break;
            case FieldIdx_prop3:
                memFieldDispatch<FieldIdx_prop3>(accessField_prop3(), std::forward<TFunc>(func));
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

    /// @brief The same as currentFieldExec()  (const variant)
    /// @details Generated for backward comatibility, can be removed in the future.
    template <typename TFunc>
    void currFieldExec(TFunc&& func) const
    {
        currentFieldExec(std::forward<TFunc>(func));
    }

    /// @brief Optimized runtime selection field functionality.
    /// @details Replaces the selectField() member function defined
    ///    by @b comms::field::Variant.
    void selectField(std::size_t idx)
    {
        if (Base::currentField() == idx) {
            return;
        }

        reset();
        switch (idx) {
            case FieldIdx_prop1: initField_prop1(); return;
            case FieldIdx_prop2: initField_prop2(); return;
            case FieldIdx_prop3: initField_prop3(); return;
            case FieldIdx_any: initField_any(); return;
            default: break;
        }
        COMMS_ASSERT(false); // Should not be reached
    }

    /// @brief Optimized reset functionality.
    /// @details Replaces the reset() member function defined
    ///    by @b comms::field::Variant.
    void reset()
    {
        if (!Base::currentFieldValid()) {
            return;
        }

        switch (Base::currentField()) {
            case FieldIdx_prop1: deinitField_prop1(); return;
            case FieldIdx_prop2: deinitField_prop2(); return;
            case FieldIdx_prop3: deinitField_prop3(); return;
            case FieldIdx_any: deinitField_any(); return;
            default: break;
        }
        COMMS_ASSERT(false); // Should not be reached
    }

    /// @brief Optimized check ability to write.
    /// @details Replaces the canWrite() member function defined
    ///    by @b comms::field::Variant.
    bool canWrite() const
    {
        if (!Base::currentFieldValid()) {
            return true;
        }

        switch (Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1().canWrite();
            case FieldIdx_prop2: return accessField_prop2().canWrite();
            case FieldIdx_prop3: return accessField_prop3().canWrite();
            case FieldIdx_any: return accessField_any().canWrite();
            default: break;
        }
        COMMS_ASSERT(false); // Should not be reached
        return false;
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto4::field::TlvPropCommon::name();
    }

    COMMS_MSVC_WARNING_PUSH
    COMMS_MSVC_WARNING_DISABLE(4702)
    /// @brief Generated read functionality.
    template <typename TIter>
    comms::ErrorStatus read(TIter& iter, std::size_t len)
    {
        reset();
        using CommonKeyField=
            comms::field::IntValue<
                howto4::field::FieldBase<>,
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
            case 0U /* 0x00U */:
                {
                    auto& field_prop1 = initField_prop1();
                    COMMS_ASSERT(field_prop1.field_key().getValue() == commonKeyField.getValue());
                    return field_prop1.template readFrom<1>(iter, len);
                }
            case 2U /* 0x02U */:
                {
                    auto& field_prop2 = initField_prop2();
                    COMMS_ASSERT(field_prop2.field_key().getValue() == commonKeyField.getValue());
                    return field_prop2.template readFrom<1>(iter, len);
                }
            case 5U /* 0x05U */:
                {
                    auto& field_prop3 = initField_prop3();
                    COMMS_ASSERT(field_prop3.field_key().getValue() == commonKeyField.getValue());
                    return field_prop3.template readFrom<1>(iter, len);
                }
            default:
                initField_any().field_key().setValue(commonKeyField.getValue());
                return accessField_any().template readFrom<1>(iter, len);
        };

        return comms::ErrorStatus::InvalidMsgData;
    }
    COMMS_MSVC_WARNING_POP

    /// @brief Generated write functionality.
    template <typename TIter>
    comms::ErrorStatus write(TIter& iter, std::size_t len) const
    {
        switch (Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1().write(iter, len);
            case FieldIdx_prop2: return accessField_prop2().write(iter, len);
            case FieldIdx_prop3: return accessField_prop3().write(iter, len);
            case FieldIdx_any: return accessField_any().write(iter, len);
            default: break;
        }

        return comms::ErrorStatus::Success;
    }

    /// @brief Generated refresh functionality.
    bool refresh()
    {
        switch (Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1().refresh();
            case FieldIdx_prop2: return accessField_prop2().refresh();
            case FieldIdx_prop3: return accessField_prop3().refresh();
            case FieldIdx_any: return accessField_any().refresh();
            default: break;
        }

        return false;
    }

    /// @brief Generated length functionality.
    std::size_t length() const
    {
        switch (Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1().length();
            case FieldIdx_prop2: return accessField_prop2().length();
            case FieldIdx_prop3: return accessField_prop3().length();
            case FieldIdx_any: return accessField_any().length();
            default: break;
        }

        return 0U;
    }

    /// @brief Generated validity check functionality.
    bool valid() const
    {
        switch (Base::currentField()) {
            case FieldIdx_prop1: return accessField_prop1().valid();
            case FieldIdx_prop2: return accessField_prop2().valid();
            case FieldIdx_prop3: return accessField_prop3().valid();
            case FieldIdx_any: return accessField_any().valid();
            default: break;
        }

        return false;
    }

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

} // namespace howto4
