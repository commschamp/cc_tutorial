// Generated by commsdsl2comms v3.4.0

/// @file
/// @brief Contains definition of <b>"TlvProp"</b> field.

#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <tuple>
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
///     @ref TlvProp bitfield.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial4::options::DefaultOptions>
struct TlvPropMembers
{
    /// @brief Scope for all the member fields of
    ///     @ref Prop4 bundle.
    struct Prop4Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        struct Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<10>,
                comms::option::def::ValidNumValue<10>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::KeyCommon::name();
            }
            
        };
        
        /// @brief Definition of <b>"Length"</b> field.
        struct Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop4MembersCommon::LengthCommon::name();
            }
            
        };
        
        /// @brief Definition of <b>"Val"</b> field.
        struct Val : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint32_t
            >
        {
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
        ///     The generated access types and functions functions are:
        ///     @li @b Field_keytype and @b field_key() access function -
        ///         for Prop4Members::Key member field.
        ///     @li @b Field_lengthtype and @b field_length() access function -
        ///         for Prop4Members::Length member field.
        ///     @li @b Field_valtype and @b field_val() access function -
        ///         for Prop4Members::Val member field.
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
    ///     @ref Prop5 bundle.
    struct Prop5Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        struct Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<15>,
                comms::option::def::ValidNumValue<15>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop5MembersCommon::KeyCommon::name();
            }
            
        };
        
        /// @brief Definition of <b>"Length"</b> field.
        struct Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
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
        
            /// @brief Default constructor.
            Val()
            {
                Base::value() = std::numeric_limits<ValueType>::infinity();
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
        ///     The generated access types and functions functions are:
        ///     @li @b Field_keytype and @b field_key() access function -
        ///         for Prop5Members::Key member field.
        ///     @li @b Field_lengthtype and @b field_length() access function -
        ///         for Prop5Members::Length member field.
        ///     @li @b Field_valtype and @b field_val() access function -
        ///         for Prop5Members::Val member field.
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
    ///     @ref Prop6 bundle.
    struct Prop6Members
    {
        /// @brief Definition of <b>"Key"</b> field.
        struct Key : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::FailOnInvalid<>,
                comms::option::def::DefaultNumValue<25>,
                comms::option::def::ValidNumValue<25>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::KeyCommon::name();
            }
            
        };
        
        /// @brief Definition of <b>"Length"</b> field.
        struct Length : public
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial4::field::TlvPropMembersCommon::Prop6MembersCommon::LengthCommon::name();
            }
            
        };
        
        /// @brief Definition of <b>"Val"</b> field.
        struct Val : public
            comms::field::String<
                tutorial4::field::FieldBase<>,
                typename TOpt::field::TlvPropMembers::Prop6Members::Val
            >
        {
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
        ///     The generated access types and functions functions are:
        ///     @li @b Field_keytype and @b field_key() access function -
        ///         for Prop6Members::Key member field.
        ///     @li @b Field_lengthtype and @b field_length() access function -
        ///         for Prop6Members::Length member field.
        ///     @li @b Field_valtype and @b field_val() access function -
        ///         for Prop6Members::Val member field.
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
    
    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           Prop4,
           Prop5,
           Prop6
        >;
};

/// @brief Definition of <b>"TlvProp"</b> field.
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
    ///     The generated types and access functions are:
    ///     @li @b Field_prop4 type, @b initField_prop4() and @b accessField_prop4() access functions -
    ///     for TlvPropMembers::Prop4 member field.
    ///     @li @b Field_prop5 type, @b initField_prop5() and @b accessField_prop5() access functions -
    ///     for TlvPropMembers::Prop5 member field.
    ///     @li @b Field_prop6 type, @b initField_prop6() and @b accessField_prop6() access functions -
    ///     for TlvPropMembers::Prop6 member field.
    COMMS_VARIANT_MEMBERS_NAMES(
        prop4,
        prop5,
        prop6
    );
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial4::field::TlvPropCommon::name();
    }
    
    /// @brief Optimized read functionality.
    template <typename TIter>
    comms::ErrorStatus read(TIter& iter, std::size_t len)
    {
        using CommonKeyField=
            comms::field::IntValue<
                tutorial4::field::FieldBase<>,
                std::uint8_t
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
    
        switch (commonKeyField.value()) {
        case 10U:
            {
                auto& field_prop4 = initField_prop4();
                COMMS_ASSERT(field_prop4.field_key().value() == commonKeyField.value());
                return field_prop4.template readFrom<1>(iter, len);
            }
        case 15U:
            {
                auto& field_prop5 = initField_prop5();
                COMMS_ASSERT(field_prop5.field_key().value() == commonKeyField.value());
                return field_prop5.template readFrom<1>(iter, len);
            }
        case 25U:
            {
                auto& field_prop6 = initField_prop6();
                COMMS_ASSERT(field_prop6.field_key().value() == commonKeyField.value());
                return field_prop6.template readFrom<1>(iter, len);
            }
        default:
            break;
        };
        return comms::ErrorStatus::InvalidMsgData;
    }
    
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
        default:
            COMMS_ASSERT(!"Invalid field execution");
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
        default:
            COMMS_ASSERT(!"Invalid field execution");
            break;
        }
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

