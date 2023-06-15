// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/ArrayList.h"
#include "comms/options.h"
#include "tutorial22/MsgId.h"
#include "tutorial22/field/FieldBase.h"
#include "tutorial22/field/TlvProp.h"
#include "tutorial22/message/Msg1Common.h"
#include "tutorial22/options/DefaultOptions.h"

namespace tutorial22
{

namespace message
{

/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile tutorial22/message/Msg1.h
template <typename TOpt = tutorial22::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::ArrayList<
            tutorial22::field::FieldBase<>,
            tutorial22::field::TlvProp<TOpt>,
            typename TOpt::message::Msg1Fields::F1
        >
    {
        using Base =
            comms::field::ArrayList<
                tutorial22::field::FieldBase<>,
                tutorial22::field::TlvProp<TOpt>,
                typename TOpt::message::Msg1Fields::F1
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial22::message::Msg1FieldsCommon::F1Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial22/message/Msg1.h
template <typename TMsgBase, typename TOpt = tutorial22::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial22::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial22::MsgId_M1>,
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
    COMMS_MSG_FIELDS_NAMES(
        f1
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 0U, "Unexpected min serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial22::message::Msg1Common::name();
    }
};

} // namespace message

} // namespace tutorial22
