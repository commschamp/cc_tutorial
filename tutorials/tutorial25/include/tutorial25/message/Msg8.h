// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of <b>"Message 8"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "tutorial25/MsgId.h"
#include "tutorial25/message/Msg8Common.h"
#include "tutorial25/options/DefaultOptions.h"

namespace tutorial25
{

namespace message
{

/// @brief Fields of @ref Msg8.
/// @tparam TOpt Extra options
/// @see @ref Msg8
/// @headerfile tutorial25/message/Msg8.h
template <typename TOpt = tutorial25::options::DefaultOptions>
struct Msg8Fields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
    >;
};

/// @brief Definition of <b>"Message 8"</b> message class.
/// @details
///     See @ref Msg8Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial25/message/Msg8.h
template <typename TMsgBase, typename TOpt = tutorial25::options::DefaultOptions>
class Msg8 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial25::MsgId_M8>,
        comms::option::def::FieldsImpl<typename Msg8Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg8<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial25::MsgId_M8>,
            comms::option::def::FieldsImpl<typename Msg8Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg8<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 0U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 0U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial25::message::Msg8Common::name();
    }
};

} // namespace message

} // namespace tutorial25
