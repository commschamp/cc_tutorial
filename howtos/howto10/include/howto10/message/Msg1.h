// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "howto10/MsgId.h"
#include "howto10/field/FieldBase.h"
#include "howto10/message/Msg1Common.h"
#include "howto10/options/DefaultOptions.h"


namespace howto10
{

namespace message
{


/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile howto10/message/Msg1.h
template <typename TOpt = howto10::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            howto10::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                howto10::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return howto10::message::Msg1FieldsCommon::F1Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return howto10::message::Msg1FieldsCommon::F1Common::name();
        }
        
    
    };
    
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile howto10/message/Msg1.h
template <typename TMsgBase, typename TOpt = howto10::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto10::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<howto10::MsgId_M1>,
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
    COMMS_MSG_FIELDS_NAMES(
        f1
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return howto10::message::Msg1Common::name();
    }
    

};

} // namespace message

} // namespace howto10

