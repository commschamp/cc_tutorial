// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of <b>"Message 3"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "tutorial9/MsgId.h"
#include "tutorial9/message/Msg3Common.h"
#include "tutorial9/options/DefaultOptions.h"

namespace tutorial9
{

namespace message
{

/// @brief Fields of @ref Msg3.
/// @tparam TOpt Extra options
/// @see @ref Msg3
/// @headerfile tutorial9/message/Msg3.h
template <typename TOpt = tutorial9::options::DefaultOptions>
struct Msg3Fields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
    >;
};

/// @brief Definition of <b>"Message 3"</b> message class.
/// @details
///     See @ref Msg3Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial9/message/Msg3.h
template <typename TMsgBase, typename TOpt = tutorial9::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        typename TOpt::message::Msg3,
        comms::option::def::StaticNumIdImpl<tutorial9::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            typename TOpt::message::Msg3,
            comms::option::def::StaticNumIdImpl<tutorial9::MsgId_M3>,
            comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
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
        return tutorial9::message::Msg3Common::name();
    }
};

} // namespace message

} // namespace tutorial9
