// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 8"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/B8_1.h"
#include "tutorial2/field/B8_2.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg8Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg8.
/// @tparam TOpt Extra options
/// @see @ref Msg8
/// @headerfile tutorial2/message/Msg8.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg8Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        tutorial2::field::B8_1<
            TOpt,
            comms::option::def::HasName
        >
    {
        using Base =
            tutorial2::field::B8_1<
                TOpt,
                comms::option::def::HasName
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg8FieldsCommon::F1Common::name();
        }
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        tutorial2::field::B8_2<
            TOpt,
            comms::option::def::HasName
        >
    {
        using Base =
            tutorial2::field::B8_2<
                TOpt,
                comms::option::def::HasName
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg8FieldsCommon::F2Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 8"</b> message class.
/// @details
///     See @ref Msg8Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg8.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg8 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M8>,
        comms::option::def::FieldsImpl<typename Msg8Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg8<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M8>,
            comms::option::def::FieldsImpl<typename Msg8Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg8<TMsgBase, TOpt> >,
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
    ///         for @ref Msg8Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg8Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 12U, "Unexpected min serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg8Common::name();
    }
};

} // namespace message

} // namespace tutorial2
