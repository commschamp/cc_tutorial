// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 11"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/F11_1.h"
#include "tutorial2/field/F11_2.h"
#include "tutorial2/field/F11_3.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg11Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg11.
/// @tparam TOpt Extra options
/// @see @ref Msg11
/// @headerfile tutorial2/message/Msg11.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg11Fields
{
    /// @brief Definition of <b>"Field 11_1"</b> field.
    using F11_1 =
        tutorial2::field::F11_1<
            TOpt,
            comms::option::def::HasName
        >;

    /// @brief Definition of <b>"Field 11_2"</b> field.
    using F2 =
        tutorial2::field::F11_2<
            TOpt,
            comms::option::def::HasName
        >;

    /// @brief Definition of <b>"F3"</b> field.
    class F3 : public
        tutorial2::field::F11_3<
            TOpt,
            comms::option::def::HasName
        >
    {
        using Base =
            tutorial2::field::F11_3<
                TOpt,
                comms::option::def::HasName
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg11FieldsCommon::F3Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F11_1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 11"</b> message class.
/// @details
///     See @ref Msg11Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg11.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg11 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M11>,
        comms::option::def::FieldsImpl<typename Msg11Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg11<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M11>,
            comms::option::def::FieldsImpl<typename Msg11Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg11<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f11_1 index, @b Field_f11_1 type and @b field_f11_1() access fuction
    ///         for @ref Msg11Fields::F11_1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg11Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg11Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        f11_1,
        f2,
        f3
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 3U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 3U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg11Common::name();
    }
};

} // namespace message

} // namespace tutorial2
