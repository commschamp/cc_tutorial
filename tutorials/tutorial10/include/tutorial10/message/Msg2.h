// Generated by commsdsl2comms v3.4.1

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "tutorial10/MsgId.h"
#include "tutorial10/message/Msg2Common.h"
#include "tutorial10/options/DefaultOptions.h"

namespace tutorial10
{

namespace message
{

/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile "tutorial10/message/Msg2.h"
template <typename TOpt = tutorial10::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
    >;
};

/// @brief Definition of <b>"Message 2"</b> message class.
/// @details
///     See @ref Msg2Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial10/message/Msg2.h"
template <typename TMsgBase, typename TOpt = tutorial10::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        typename TOpt::message::Msg2,
        comms::option::def::StaticNumIdImpl<tutorial10::MsgId_M2>,
        comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            typename TOpt::message::Msg2,
            comms::option::def::StaticNumIdImpl<tutorial10::MsgId_M2>,
            comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
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
        return tutorial10::message::Msg2Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial10


