// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/options.h"
#include "t23_ext/ns1/field/S1.h"
#include "tutorial23/MsgId.h"
#include "tutorial23/field/FieldBase.h"
#include "tutorial23/field/I1.h"
#include "tutorial23/message/Msg1Common.h"
#include "tutorial23/options/DefaultOptions.h"

namespace tutorial23
{

namespace message
{

/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile tutorial23/message/Msg1.h
template <typename TOpt = tutorial23::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        tutorial23::field::I1<
            TOpt,
            comms::option::def::HasName
        >
    {
        using Base =
            tutorial23::field::I1<
                TOpt,
                comms::option::def::HasName
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial23::message::Msg1FieldsCommon::F1Common::name();
        }
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        t23_ext::ns1::field::S1<
            TOpt,
            typename TOpt::tutorial23::message::Msg1Fields::F2,
            comms::option::def::HasName
        >
    {
        using Base =
            t23_ext::ns1::field::S1<
                TOpt,
                typename TOpt::tutorial23::message::Msg1Fields::F2,
                comms::option::def::HasName
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial23::message::Msg1FieldsCommon::F2Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial23/message/Msg1.h
template <typename TMsgBase, typename TOpt = tutorial23::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial23::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial23::MsgId_M1>,
            comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
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
    ///         for @ref Msg1Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg1Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 3U, "Unexpected min serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial23::message::Msg1Common::name();
    }
};

} // namespace message

} // namespace tutorial23
