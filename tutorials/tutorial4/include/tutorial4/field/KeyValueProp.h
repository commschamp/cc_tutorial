// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"KeyValueProp"</b> field.

#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <tuple>
#include "comms/Assert.h"
#include "comms/CompileControl.h"
#include "comms/field/Bundle.h"
#include "comms/field/FloatValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/field/Variant.h"
#include "comms/options.h"
#include "tutorial4/field/FieldBase.h"
#include "tutorial4/field/KeyValuePropCommon.h"
#include "tutorial4/options/DefaultOptions.h"

namespace tutorial4
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref KeyValueProp field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial4::options::DefaultOptions>
struct KeyValuePropMembers
{
    /// @brief Scope for all the member fields of
    ///     @ref Prop1 field.
    struct Prop1Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::ValidNumValue<0>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
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
                return tutorial4::field::KeyValuePropMembersCommon::Prop1MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop1MembersCommon::KeyCommon::name();
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

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop1MembersCommon::ValCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop1MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop1"</b> field.
    class Prop1 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop1Members::All,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop1Members::All,
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
        ///         for tutorial4::field::KeyValuePropMembers::Prop1Members::Key member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::KeyValuePropMembers::Prop1Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::KeyValuePropMembersCommon::Prop1Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop2 field.
    struct Prop2Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<2>,
                comms::option::def::ValidNumValue<2>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
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
                return tutorial4::field::KeyValuePropMembersCommon::Prop2MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop2MembersCommon::KeyCommon::name();
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

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::FloatValue<
                tutorial4::field::FieldBase<>,
                float
            >
        {
            using Base =
                comms::field::FloatValue<
                    tutorial4::field::FieldBase<>,
                    float
                >;
        public:
            /// @brief Default constructor.
            Val()
            {
                Base::setValue(std::numeric_limits<ValueType>::quiet_NaN());
            }

            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop2MembersCommon::ValCommon::hasSpecials();
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
                return tutorial4::field::KeyValuePropMembersCommon::Prop2MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop2"</b> field.
    class Prop2 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop2Members::All,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop2Members::All,
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
        ///         for tutorial4::field::KeyValuePropMembers::Prop2Members::Key member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::KeyValuePropMembers::Prop2Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::KeyValuePropMembersCommon::Prop2Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref Prop3 field.
    struct Prop3Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        class Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<5>,
                comms::option::def::ValidNumValue<5>,
                comms::option::def::HasCustomRefresh
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial4::field::FieldBase<>,
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
                return tutorial4::field::KeyValuePropMembersCommon::Prop3MembersCommon::KeyCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop3MembersCommon::KeyCommon::name();
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

        /// @brief Scope for all the member fields of
        ///     @ref Val field.
        struct ValMembers
        {
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
                    return tutorial4::field::KeyValuePropMembersCommon::Prop3MembersCommon::ValMembersCommon::LengthCommon::hasSpecials();
                }

                /// @brief Name of the field.
                static const char* name()
                {
                    return tutorial4::field::KeyValuePropMembersCommon::Prop3MembersCommon::ValMembersCommon::LengthCommon::name();
                }
            };
        };

        /// @brief Definition of <b>"Val"</b> field.
        class Val : public
            comms::field::String<
                tutorial4::field::FieldBase<>,
                typename TOpt::field::KeyValuePropMembers::Prop3Members::Val,
                comms::option::def::SequenceSerLengthFieldPrefix<typename ValMembers::Length>
            >
        {
            using Base =
                comms::field::String<
                    tutorial4::field::FieldBase<>,
                    typename TOpt::field::KeyValuePropMembers::Prop3Members::Val,
                    comms::option::def::SequenceSerLengthFieldPrefix<typename ValMembers::Length>
                >;
        public:
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::KeyValuePropMembersCommon::Prop3MembersCommon::ValCommon::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               Key,
               Val
            >;
    };

    /// @brief Definition of <b>"Prop3"</b> field.
    class Prop3 : public
        comms::field::Bundle<
            tutorial4::field::FieldBase<>,
            typename Prop3Members::All,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial4::field::FieldBase<>,
                typename Prop3Members::All,
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
        ///         for tutorial4::field::KeyValuePropMembers::Prop3Members::Key member field.
        ///     @li @b FieldIdx_val index, @b Field_val type and @b field_val() access function -
        ///         for tutorial4::field::KeyValuePropMembers::Prop3Members::Val member field.
        COMMS_FIELD_MEMBERS_NAMES(
            key,
            val
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial4::field::KeyValuePropMembersCommon::Prop3Common::name();
        }
    };

    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           Prop1,
           Prop2,
           Prop3
        >;
};

/// @brief Definition of <b>"KeyValueProp"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial4::options::DefaultOptions, typename... TExtraOpts>
class KeyValueProp : public
    comms::field::Variant<
        tutorial4::field::FieldBase<>,
        typename KeyValuePropMembers<TOpt>::All,
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
            tutorial4::field::FieldBase<>,
            typename KeyValuePropMembers<TOpt>::All,
            TExtraOpts...,
            comms::option::def::HasCustomRead,
            comms::option::def::HasCustomWrite,
            comms::option::def::HasCustomRefresh,
            comms::option::def::VariantHasCustomResetOnDestruct,
            comms::option::def::HasVersionDependentMembers<false>
        >;
public:
    /// @brief Default constructor.
    KeyValueProp() = default;

    /// @brief Destructor
    ~KeyValueProp()
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
    ///         for tutorial4::field::KeyValuePropMembers::Prop1 member field.
    ///     @li @b FieldIdx_prop2 index, @b Field_prop2 type,
    ///         @b initField_prop2(), @b deinitField_prop2() and @b accessField_prop2() access functions -
    ///         for tutorial4::field::KeyValuePropMembers::Prop2 member field.
    ///     @li @b FieldIdx_prop3 index, @b Field_prop3 type,
    ///         @b initField_prop3(), @b deinitField_prop3() and @b accessField_prop3() access functions -
    ///         for tutorial4::field::KeyValuePropMembers::Prop3 member field.
    COMMS_VARIANT_MEMBERS_NAMES(
        prop1,
        prop2,
        prop3
    );

    /// @brief Copy constructor.
    KeyValueProp(const KeyValueProp& other) :
        Base()
    {
        *this = other;
    }

    /// @brief Move constructor.
    KeyValueProp(KeyValueProp&& other) : 
        Base()
    {
        *this = std::move(other);
    }

    /// @brief Copy assignment operator.
    KeyValueProp& operator=(const KeyValueProp& other)
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
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return *this;
    }

    /// @brief Move assignement operator.
    KeyValueProp& operator=(KeyValueProp&& other)
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
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return *this;
    }

    /// @brief Equality comparison operator.
    bool operator==(const KeyValueProp& other) const
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
            default: break;
        }

        COMMS_ASSERT(false); // Should not be reached
        return false;
    }

    /// @brief Inequality comparison operator.
    bool operator!=(const KeyValueProp& other) const
    {
        return !(*this == other);
    }

    /// @brief Order comparison operator.
    bool operator<(const KeyValueProp& other) const
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
        switch (Base::currentField()) {
            case FieldIdx_prop1: initField_prop1(); return;
            case FieldIdx_prop2: initField_prop2(); return;
            case FieldIdx_prop3: initField_prop3(); return;
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
            default: break;
        }
        COMMS_ASSERT(false); // Should not be reached
        return false;
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial4::field::KeyValuePropCommon::name();
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
                break;
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

} // namespace tutorial4
