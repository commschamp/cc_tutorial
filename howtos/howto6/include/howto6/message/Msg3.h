// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 3"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "howto6/MsgId.h"
#include "howto6/field/FieldBase.h"
#include "howto6/message/Msg3Common.h"
#include "howto6/options/DefaultOptions.h"

namespace howto6
{

namespace message
{

/// @brief Fields of @ref Msg3.
/// @tparam TOpt Extra options
/// @see @ref Msg3
/// @headerfile howto6/message/Msg3.h
template <typename TOpt = howto6::options::DefaultOptions>
struct Msg3Fields
{
    /// @brief Scope for all the member fields of
    ///     @ref F1 field.
    struct F1Members
    {
        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                howto6::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    howto6::field::FieldBase<>,
                    std::uint8_t,
                    comms::option::def::HasName
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto6::message::Msg3FieldsCommon::F1MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto6::message::Msg3FieldsCommon::F1MembersCommon::LengthCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::String<
            howto6::field::FieldBase<>,
            typename TOpt::message::Msg3Fields::F1,
            comms::option::def::HasName,
            comms::option::def::SequenceSerLengthFieldPrefix<typename F1Members::Length>
        >
    {
        using Base =
            comms::field::String<
                howto6::field::FieldBase<>,
                typename TOpt::message::Msg3Fields::F1,
                comms::option::def::HasName,
                comms::option::def::SequenceSerLengthFieldPrefix<typename F1Members::Length>
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return howto6::message::Msg3FieldsCommon::F1Common::name();
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
/// @headerfile howto6/message/Msg3.h
template <typename TMsgBase, typename TOpt = howto6::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto6::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<howto6::MsgId_M3>,
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
    COMMS_MSG_FIELDS_NAMES(
        f1
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 1U, "Unexpected min serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return howto6::message::Msg3Common::name();
    }
};

} // namespace message

} // namespace howto6
