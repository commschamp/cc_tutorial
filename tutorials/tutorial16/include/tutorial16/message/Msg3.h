// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"Message 3"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial16/MsgId.h"
#include "tutorial16/field/FieldBase.h"
#include "tutorial16/message/Msg3Common.h"
#include "tutorial16/options/DefaultOptions.h"

namespace tutorial16
{

namespace message
{

/// @brief Fields of @ref Msg3.
/// @tparam TOpt Extra options
/// @see @ref Msg3
/// @headerfile tutorial16/message/Msg3.h
template <typename TOpt = tutorial16::options::DefaultOptions>
struct Msg3Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            tutorial16::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial16::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial16::message::Msg3FieldsCommon::F1Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial16::message::Msg3FieldsCommon::F1Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 3"</b> message class.
/// @details
///     See @ref Msg3Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial16/message/Msg3.h
template <typename TMsgBase, typename TOpt = tutorial16::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial16::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial16::MsgId_M3>,
            comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    Msg3()
    {
        Base::transportField_flags().setBitValue_B2(true);
    }

    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg3Fields::F1 field.
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
        return tutorial16::message::Msg3Common::name();
    }

    /// @brief Generated read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        bool validRead =
            Base::transportField_flags().getBitValue_B2();

        if (!validRead) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::doRead(iter, len);
    }
};

} // namespace message

} // namespace tutorial16
