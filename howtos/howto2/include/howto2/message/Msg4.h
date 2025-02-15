// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 4"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "howto2/MsgId.h"
#include "howto2/field/FieldBase.h"
#include "howto2/message/Msg4Common.h"
#include "howto2/options/DefaultOptions.h"

namespace howto2
{

namespace message
{

/// @brief Fields of @ref Msg4.
/// @tparam TOpt Extra options
/// @see @ref Msg4
/// @headerfile howto2/message/Msg4.h
template <typename TOpt = howto2::options::DefaultOptions>
struct Msg4Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            howto2::field::FieldBase<>,
            std::uint16_t,
            comms::option::def::HasName,
            comms::option::def::DefaultNumValue<60000L>
        >
    {
        using Base =
            comms::field::IntValue<
                howto2::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName,
                comms::option::def::DefaultNumValue<60000L>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return howto2::message::Msg4FieldsCommon::F1Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return howto2::message::Msg4FieldsCommon::F1Common::name();
        }
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::IntValue<
            howto2::field::FieldBase<>,
            std::uint16_t,
            comms::option::def::HasName,
            comms::option::def::DefaultNumValue<22222>
        >
    {
        using Base =
            comms::field::IntValue<
                howto2::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName,
                comms::option::def::DefaultNumValue<22222>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return howto2::message::Msg4FieldsCommon::F2Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return howto2::message::Msg4FieldsCommon::F2Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 4"</b> message class.
/// @details
///     See @ref Msg4Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile howto2/message/Msg4.h
template <typename TMsgBase, typename TOpt = howto2::options::DefaultOptions>
class Msg4 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto2::MsgId_M4>,
        comms::option::def::FieldsImpl<typename Msg4Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg4<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<howto2::MsgId_M4>,
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
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 4U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 4U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return howto2::message::Msg4Common::name();
    }
};

} // namespace message

} // namespace howto2
