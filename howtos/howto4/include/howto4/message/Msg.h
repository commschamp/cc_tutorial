// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"Message"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/ArrayList.h"
#include "comms/options.h"
#include "howto4/MsgId.h"
#include "howto4/field/FieldBase.h"
#include "howto4/field/TlvProp.h"
#include "howto4/message/MsgCommon.h"
#include "howto4/options/DefaultOptions.h"

namespace howto4
{

namespace message
{

/// @brief Fields of @ref Msg.
/// @tparam TOpt Extra options
/// @see @ref Msg
/// @headerfile howto4/message/Msg.h
template <typename TOpt = howto4::options::DefaultOptions>
struct MsgFields
{
    /// @brief Definition of <b>"Props"</b> field.
    class Props : public
        comms::field::ArrayList<
            howto4::field::FieldBase<>,
            howto4::field::TlvProp<TOpt>,
            typename TOpt::message::MsgFields::Props
        >
    {
        using Base =
            comms::field::ArrayList<
                howto4::field::FieldBase<>,
                howto4::field::TlvProp<TOpt>,
                typename TOpt::message::MsgFields::Props
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return howto4::message::MsgFieldsCommon::PropsCommon::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Props
    >;
};

/// @brief Definition of <b>"Message"</b> message class.
/// @details
///     See @ref MsgFields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile howto4/message/Msg.h
template <typename TMsgBase, typename TOpt = howto4::options::DefaultOptions>
class Msg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto4::MsgId_M0>,
        comms::option::def::FieldsImpl<typename MsgFields<TOpt>::All>,
        comms::option::def::MsgType<Msg<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<howto4::MsgId_M0>,
            comms::option::def::FieldsImpl<typename MsgFields<TOpt>::All>,
            comms::option::def::MsgType<Msg<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_props index, @b Field_props type and @b field_props() access fuction
    ///         for @ref MsgFields::Props field.
    COMMS_MSG_FIELDS_NAMES(
        props
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 0U, "Unexpected min serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return howto4::message::MsgCommon::name();
    }
};

} // namespace message

} // namespace howto4
