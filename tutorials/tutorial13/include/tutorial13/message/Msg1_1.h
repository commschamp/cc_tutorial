// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"Message 1 (1)"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial13/MsgId.h"
#include "tutorial13/field/FieldBase.h"
#include "tutorial13/message/Msg1_1Common.h"
#include "tutorial13/options/DefaultOptions.h"

namespace tutorial13
{

namespace message
{

/// @brief Fields of @ref Msg1_1.
/// @tparam TOpt Extra options
/// @see @ref Msg1_1
/// @headerfile "tutorial13/message/Msg1_1.h"
template <typename TOpt = tutorial13::options::DefaultOptions>
struct Msg1_1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::IntValue<
            tutorial13::field::FieldBase<>,
            std::uint64_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial13::message::Msg1_1FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 1 (1)"</b> message class.
/// @details
///     See @ref Msg1_1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial13/message/Msg1_1.h"
template <typename TMsgBase, typename TOpt = tutorial13::options::DefaultOptions>
class Msg1_1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial13::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1_1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1_1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial13::MsgId_M1>,
            comms::option::def::FieldsImpl<typename Msg1_1Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg1_1<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg1_1Fields::F1 field.
    COMMS_MSG_FIELDS_NAMES(
        f1
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 8U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 8U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial13::message::Msg1_1Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial13


