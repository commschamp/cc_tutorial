// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/FloatValue.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial3/MsgId.h"
#include "tutorial3/field/FieldBase.h"
#include "tutorial3/message/Msg2Common.h"
#include "tutorial3/options/DefaultOptions.h"


namespace tutorial3
{

namespace message
{


/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile tutorial3/message/Msg2.h
template <typename TOpt = tutorial3::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            tutorial3::field::FieldBase<>,
            std::uint32_t,
            comms::option::def::UnitsSeconds
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial3::field::FieldBase<>,
                std::uint32_t,
                comms::option::def::UnitsSeconds
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial3::message::Msg2FieldsCommon::F1Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial3::message::Msg2FieldsCommon::F1Common::name();
        }
        
    
    };
    
    
    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::FloatValue<
            tutorial3::field::FieldBase<>,
            double,
            comms::option::def::UnitsMillimeters
        >
    {
        using Base =
            comms::field::FloatValue<
                tutorial3::field::FieldBase<>,
                double,
                comms::option::def::UnitsMillimeters
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial3::message::Msg2FieldsCommon::F2Common::hasSpecials();
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
            return tutorial3::message::Msg2FieldsCommon::F2Common::name();
        }
        
    
    };
    
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 2"</b> message class.
/// @details
///     See @ref Msg2Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial3/message/Msg2.h
template <typename TMsgBase, typename TOpt = tutorial3::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial3::MsgId_M2>,
        comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial3::MsgId_M2>,
            comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
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
    ///         for @ref Msg2Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg2Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 12U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 12U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial3::message::Msg2Common::name();
    }
    

};

} // namespace message

} // namespace tutorial3


