// Generated by commsdsl2comms v6.3.3

/// @file
/// @brief Contains definition of <b>"Message 4"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/S4_1.h"
#include "tutorial2/field/S4_2.h"
#include "tutorial2/field/S4_3.h"
#include "tutorial2/message/Msg4Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg4.
/// @tparam TOpt Extra options
/// @see @ref Msg4
/// @headerfile tutorial2/message/Msg4.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg4Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        tutorial2::field::S4_1<
            TOpt
        >
    {
        using Base =
            tutorial2::field::S4_1<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg4FieldsCommon::F1Common::name();
        }
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        tutorial2::field::S4_2<
            TOpt
        >
    {
        using Base =
            tutorial2::field::S4_2<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg4FieldsCommon::F2Common::name();
        }
    };

    /// @brief Definition of <b>"F3"</b> field.
    class F3 : public
        tutorial2::field::S4_3<
            TOpt
        >
    {
        using Base =
            tutorial2::field::S4_3<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg4FieldsCommon::F3Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 4"</b> message class.
/// @details
///     See @ref Msg4Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg4.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg4 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M4>,
        comms::option::def::FieldsImpl<typename Msg4Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg4<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M4>,
            comms::option::def::FieldsImpl<typename Msg4Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg4<TMsgBase, TOpt> >,
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
    ///         for @ref Msg4Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg4Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg4Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 6U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 6U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg4Common::name();
    }
};

} // namespace message

} // namespace tutorial2
