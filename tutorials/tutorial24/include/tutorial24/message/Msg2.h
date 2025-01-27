// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial24/MsgId.h"
#include "tutorial24/field/FieldBase.h"
#include "tutorial24/message/Msg2Common.h"
#include "tutorial24/options/DefaultOptions.h"

namespace tutorial24
{

namespace message
{

/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile tutorial24/message/Msg2.h
template <typename TOpt = tutorial24::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            tutorial24::field::FieldBase<>,
            std::uint8_t,
            comms::option::def::HasName,
            comms::option::def::ValidNumValueRange<0, 10>
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial24::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::HasName,
                comms::option::def::ValidNumValueRange<0, 10>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial24::message::Msg2FieldsCommon::F1Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial24::message::Msg2FieldsCommon::F1Common::name();
        }
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::IntValue<
            tutorial24::field::FieldBase<>,
            std::uint8_t,
            comms::option::def::HasName,
            comms::option::def::ValidNumValueRange<10, 20>
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial24::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::HasName,
                comms::option::def::ValidNumValueRange<10, 20>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial24::message::Msg2FieldsCommon::F2Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial24::message::Msg2FieldsCommon::F2Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 2"</b> message class.
/// @details
///     See @ref Msg2Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial24/message/Msg2.h
template <typename TMsgBase, typename TOpt = tutorial24::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial24::MsgId_M2>,
        comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::FailOnInvalid<>
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial24::MsgId_M2>,
            comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
            comms::option::def::HasName,
            comms::option::def::FailOnInvalid<>
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg2Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg2Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial24::message::Msg2Common::name();
    }
};

} // namespace message

} // namespace tutorial24