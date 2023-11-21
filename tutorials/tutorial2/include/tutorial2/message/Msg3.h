// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of <b>"Message 3"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/I3_1.h"
#include "tutorial2/field/I3_2.h"
#include "tutorial2/field/I3_3.h"
#include "tutorial2/field/I3_4.h"
#include "tutorial2/field/I3_5.h"
#include "tutorial2/message/Msg3Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg3.
/// @tparam TOpt Extra options
/// @see @ref Msg3
/// @headerfile tutorial2/message/Msg3.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg3Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        tutorial2::field::I3_1<
            TOpt
        >
    {
        using Base =
            tutorial2::field::I3_1<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg3FieldsCommon::F1Common::name();
        }
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        tutorial2::field::I3_2<
            TOpt
        >
    {
        using Base =
            tutorial2::field::I3_2<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg3FieldsCommon::F2Common::name();
        }
    };

    /// @brief Definition of <b>"F3"</b> field.
    class F3 : public
        tutorial2::field::I3_3<
            TOpt
        >
    {
        using Base =
            tutorial2::field::I3_3<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg3FieldsCommon::F3Common::name();
        }
    };

    /// @brief Definition of <b>"F4"</b> field.
    class F4 : public
        tutorial2::field::I3_4<
            TOpt
        >
    {
        using Base =
            tutorial2::field::I3_4<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg3FieldsCommon::F4Common::name();
        }
    };

    /// @brief Definition of <b>"F5"</b> field.
    class F5 : public
        tutorial2::field::I3_5<
            TOpt
        >
    {
        using Base =
            tutorial2::field::I3_5<
                TOpt
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg3FieldsCommon::F5Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3,
        F4,
        F5
    >;
};

/// @brief Definition of <b>"Message 3"</b> message class.
/// @details
///     See @ref Msg3Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg3.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M3>,
            comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
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
    ///         for @ref Msg3Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg3Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg3Fields::F3 field.
    ///     @li @b FieldIdx_f4 index, @b Field_f4 type and @b field_f4() access fuction
    ///         for @ref Msg3Fields::F4 field.
    ///     @li @b FieldIdx_f5 index, @b Field_f5 type and @b field_f5() access fuction
    ///         for @ref Msg3Fields::F5 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3,
        f4,
        f5
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 10U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 13U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg3Common::name();
    }
};

} // namespace message

} // namespace tutorial2
