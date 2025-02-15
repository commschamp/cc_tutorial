// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Connect"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/options.h"
#include "tutorial20/MsgId.h"
#include "tutorial20/field/FieldBase.h"
#include "tutorial20/field/Version.h"
#include "tutorial20/message/ConnectCommon.h"
#include "tutorial20/options/DefaultOptions.h"

namespace tutorial20
{

namespace message
{

/// @brief Fields of @ref Connect.
/// @tparam TOpt Extra options
/// @see @ref Connect
/// @headerfile tutorial20/message/Connect.h
template <typename TOpt = tutorial20::options::DefaultOptions>
struct ConnectFields
{
    /// @brief Definition of <b>"Version"</b> field.
    using Version =
        tutorial20::field::Version<
            TOpt,
            comms::option::def::HasName
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Version
    >;
};

/// @brief Definition of <b>"Connect"</b> message class.
/// @details
///     See @ref ConnectFields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial20/message/Connect.h
template <typename TMsgBase, typename TOpt = tutorial20::options::DefaultOptions>
class Connect : public
    comms::MessageBase<
        TMsgBase,
        typename TOpt::message::Connect,
        comms::option::def::StaticNumIdImpl<tutorial20::MsgId_Connect>,
        comms::option::def::FieldsImpl<typename ConnectFields<TOpt>::All>,
        comms::option::def::MsgType<Connect<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            typename TOpt::message::Connect,
            comms::option::def::StaticNumIdImpl<tutorial20::MsgId_Connect>,
            comms::option::def::FieldsImpl<typename ConnectFields<TOpt>::All>,
            comms::option::def::MsgType<Connect<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_version index, @b Field_version type and @b field_version() access fuction
    ///         for @ref ConnectFields::Version field.
    COMMS_MSG_FIELDS_NAMES(
        version
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial20::message::ConnectCommon::name();
    }
};

} // namespace message

} // namespace tutorial20
