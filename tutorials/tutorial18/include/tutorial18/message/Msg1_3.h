// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains definition of <b>"Message 1 (3)"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial18/MsgId.h"
#include "tutorial18/field/FieldBase.h"
#include "tutorial18/message/Msg1_3Common.h"
#include "tutorial18/options/DefaultOptions.h"

namespace tutorial18
{

namespace message
{

/// @brief Fields of @ref Msg1_3.
/// @tparam TOpt Extra options
/// @see @ref Msg1_3
/// @headerfile tutorial18/message/Msg1_3.h
template <typename TOpt = tutorial18::options::DefaultOptions>
struct Msg1_3Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            tutorial18::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial18::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial18::message::Msg1_3FieldsCommon::F1Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial18::message::Msg1_3FieldsCommon::F1Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 1 (3)"</b> message class.
/// @details
///     See @ref Msg1_3Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial18/message/Msg1_3.h
template <typename TMsgBase, typename TOpt = tutorial18::options::DefaultOptions>
class Msg1_3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial18::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1_3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1_3<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial18::MsgId_M1>,
            comms::option::def::FieldsImpl<typename Msg1_3Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg1_3<TMsgBase, TOpt> >,
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
    ///         for @ref Msg1_3Fields::F1 field.
    COMMS_MSG_FIELDS_NAMES(
        f1
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial18::message::Msg1_3Common::name();
    }
};

} // namespace message

} // namespace tutorial18
