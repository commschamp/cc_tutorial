// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial20/MsgId.h"
#include "tutorial20/field/FieldBase.h"
#include "tutorial20/message/Msg1Common.h"
#include "tutorial20/options/DefaultOptions.h"


namespace tutorial20
{

namespace message
{


/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile tutorial20/message/Msg1.h
template <typename TOpt = tutorial20::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            tutorial20::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial20::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial20::message::Msg1FieldsCommon::F1Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial20::message::Msg1FieldsCommon::F1Common::name();
        }
        
    
    };
    
    
    /// @brief Inner field of @ref F2 optional.
    /// @deprecated Since version 4
    
    class F2Field : public
        comms::field::IntValue<
            tutorial20::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial20::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial20::message::Msg1FieldsCommon::F2Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial20::message::Msg1FieldsCommon::F2Common::name();
        }
        
    
    };
    
    /// @brief Definition of version dependent
    ///     <b>F2</b> field.
    struct F2 : public
        comms::field::Optional<
            F2Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<2U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F2Field::name();
        }
    };
    
    
    /// @brief Inner field of @ref F3 optional.
    class F3Field : public
        comms::field::IntValue<
            tutorial20::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial20::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial20::message::Msg1FieldsCommon::F3Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial20::message::Msg1FieldsCommon::F3Common::name();
        }
        
    
    };
    
    /// @brief Definition of version dependent
    ///     <b>F3</b> field.
    struct F3 : public
        comms::field::Optional<
            F3Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<5U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F3Field::name();
        }
    };
    
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial20/message/Msg1.h
template <typename TMsgBase, typename TOpt = tutorial20::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial20::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial20::MsgId_M1>,
            comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg1Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg1Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg1Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 6U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial20::message::Msg1Common::name();
    }
    

};

} // namespace message

} // namespace tutorial20


