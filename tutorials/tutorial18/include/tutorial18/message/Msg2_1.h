// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of <b>"Message 2 (1)"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial18/MsgId.h"
#include "tutorial18/field/FieldBase.h"
#include "tutorial18/message/Msg2_1Common.h"
#include "tutorial18/options/DefaultOptions.h"

namespace tutorial18
{

namespace message
{

/// @brief Fields of @ref Msg2_1.
/// @tparam TOpt Extra options
/// @see @ref Msg2_1
/// @headerfile "tutorial18/message/Msg2_1.h"
template <typename TOpt = tutorial18::options::DefaultOptions>
struct Msg2_1Fields
{
    /// @brief Definition of <b>"Type"</b> field.
    struct Type : public
        comms::field::IntValue<
            tutorial18::field::FieldBase<>,
            std::uint8_t,
            comms::option::def::FailOnInvalid<>,
            comms::option::def::DefaultNumValue<1>,
            comms::option::def::ValidNumValue<1>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial18::message::Msg2_1FieldsCommon::TypeCommon::name();
        }
        
    };
    
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::IntValue<
            tutorial18::field::FieldBase<>,
            std::uint16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial18::message::Msg2_1FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Type,
        F1
    >;
};

/// @brief Definition of <b>"Message 2 (1)"</b> message class.
/// @details
///     See @ref Msg2_1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial18/message/Msg2_1.h"
template <typename TMsgBase, typename TOpt = tutorial18::options::DefaultOptions>
class Msg2_1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial18::MsgId_M2>,
        comms::option::def::FieldsImpl<typename Msg2_1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg2_1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial18::MsgId_M2>,
            comms::option::def::FieldsImpl<typename Msg2_1Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg2_1<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_type index, @b Field_type type and @b field_type() access fuction
    ///         for @ref Msg2_1Fields::Type field.
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg2_1Fields::F1 field.
    COMMS_MSG_FIELDS_NAMES(
        type,
        f1
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 3U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 3U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial18::message::Msg2_1Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial18


