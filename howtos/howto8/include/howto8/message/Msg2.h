// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "howto8/MsgId.h"
#include "howto8/field/FieldBase.h"
#include "howto8/message/Msg2Common.h"
#include "howto8/options/DefaultOptions.h"

namespace howto8
{

namespace message
{

/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile howto8/message/Msg2.h
template <typename TOpt = howto8::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            howto8::field::FieldBase<>,
            std::uint32_t
        >
    {
        using Base =
            comms::field::IntValue<
                howto8::field::FieldBase<>,
                std::uint32_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return howto8::message::Msg2FieldsCommon::F1Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return howto8::message::Msg2FieldsCommon::F1Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F2 field.
    struct F2Members
    {
        /// @brief Definition of <b>"F2Field"</b> field.
        class F2Field : public
            comms::field::IntValue<
                howto8::field::FieldBase<>,
                std::uint32_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto8::field::FieldBase<>,
                    std::uint32_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto8::message::Msg2FieldsCommon::F2MembersCommon::F2FieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto8::message::Msg2FieldsCommon::F2MembersCommon::F2FieldCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F2"</b> field.
    /// @details
    ///     Present when B1 in the interface flags is set
    class F2 : public
        comms::field::Optional<
            typename F2Members::F2Field,
            comms::option::def::MissingByDefault
        >
    {
        using Base =
            comms::field::Optional<
                typename F2Members::F2Field,
                comms::option::def::MissingByDefault
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return howto8::message::Msg2FieldsCommon::F2Common::name();
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
/// @headerfile howto8/message/Msg2.h
template <typename TMsgBase, typename TOpt = howto8::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto8::MsgId_M2>,
        comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::HasCustomRefresh
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<howto8::MsgId_M2>,
            comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
            comms::option::def::HasName,
            comms::option::def::HasCustomRefresh
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
    static_assert(MsgMinLen == 4U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 8U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return howto8::message::Msg2Common::name();
    }

    /// @brief Custom read functionality
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        doRefresh(); // Update mode according to flags in the interface
        return Base::doRead(iter, len);
    }

    // @brief Custom refresh functionality
    bool doRefresh()
    {
        bool updated = Base::doRefresh(); // Don't forget default refresh functionality

        auto expF2Mode = comms::field::OptionalMode::Missing;
        if (Base::transportField_flags().getBitValue_B1()) {
            expF2Mode = comms::field::OptionalMode::Exists;
        }

        if (field_f2().getMode() == expF2Mode) {
            return updated;
        }

        field_f2().setMode(expF2Mode);
        return true;
    }
};

} // namespace message

} // namespace howto8
