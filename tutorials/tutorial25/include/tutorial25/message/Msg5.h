// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of <b>"Message 5"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "tutorial25/MsgId.h"
#include "tutorial25/message/Msg5Common.h"
#include "tutorial25/options/DefaultOptions.h"

namespace tutorial25
{

namespace message
{

/// @brief Fields of @ref Msg5.
/// @tparam TOpt Extra options
/// @see @ref Msg5
/// @headerfile tutorial25/message/Msg5.h
template <typename TOpt = tutorial25::options::DefaultOptions>
struct Msg5Fields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
    >;
};

/// @brief Definition of <b>"Message 5"</b> message class.
/// @details
///     See @ref Msg5Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial25/message/Msg5.h
template <typename TMsgBase, typename TOpt = tutorial25::options::DefaultOptions>
class Msg5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial25::MsgId_M5>,
        comms::option::def::FieldsImpl<typename Msg5Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg5<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial25::MsgId_M5>,
            comms::option::def::FieldsImpl<typename Msg5Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg5<TMsgBase, TOpt> >,
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
        return tutorial25::message::Msg5Common::name();
    }
};

} // namespace message

} // namespace tutorial25
