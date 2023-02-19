// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "howto5/MsgId.h"
#include "howto5/field/FieldBase.h"
#include "howto5/message/Msg2Common.h"
#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace message
{

/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile howto5/message/Msg2.h
template <typename TOpt = howto5::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Scope for all the member fields of
    ///     @ref F1 field.
    struct F1Members
    {
        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
            comms::field::IntValue<
                howto5::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto5::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto5::message::Msg2FieldsCommon::F1MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto5::message::Msg2FieldsCommon::F1MembersCommon::LengthCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::String<
            howto5::field::FieldBase<>,
            typename TOpt::message::Msg2Fields::F1,
            comms::option::def::SequenceSerLengthFieldPrefix<typename F1Members::Length>
        >
    {
        using Base =
            comms::field::String<
                howto5::field::FieldBase<>,
                typename TOpt::message::Msg2Fields::F1,
                comms::option::def::SequenceSerLengthFieldPrefix<typename F1Members::Length>
            >;
    public:
        /// @brief Default constructor
        F1()
        {
            static const char Str[] = "hello";
            static const std::size_t StrSize = std::extent<decltype(Str)>::value;
            Base::setValue(typename Base::ValueType(&Str[0], StrSize - 1));
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::message::Msg2FieldsCommon::F1Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F2 field.
    struct F2Members
    {
        /// @brief Definition of <b>"F2"</b> field.
        class Field : public
            comms::field::IntValue<
                howto5::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    howto5::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return howto5::message::Msg2FieldsCommon::F2MembersCommon::FieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return howto5::message::Msg2FieldsCommon::F2MembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F2"</b> field.
    /// @details
    ///     The field exists only when B1 in interface flags is set.
    class F2 : public
        comms::field::Optional<
            typename F2Members::Field,
            comms::option::def::MissingByDefault
        >
    {
        using Base =
            comms::field::Optional<
                typename F2Members::Field,
                comms::option::def::MissingByDefault
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::message::Msg2FieldsCommon::F2Common::name();
        }
    };

    /// @brief Inner field of @ref F3 optional.
    class F3Field : public
        comms::field::IntValue<
            howto5::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                howto5::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return howto5::message::Msg2FieldsCommon::F3Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::message::Msg2FieldsCommon::F3Common::name();
        }
    };

    /// @brief Definition of version dependent
    ///     <b>F3</b> field.
    struct F3 : public
        comms::field::Optional<
            F3Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<3U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F3Field::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 2"</b> message class.
/// @details
///     See @ref Msg2Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile howto5/message/Msg2.h
template <typename TMsgBase, typename TOpt = howto5::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto5::MsgId_M2>,
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
            comms::option::def::StaticNumIdImpl<howto5::MsgId_M2>,
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
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg2Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 1U, "Unexpected min serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return howto5::message::Msg2Common::name();
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

} // namespace howto5
