// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Message 17"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/Bundle.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg17Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg17.
/// @tparam TOpt Extra options
/// @see @ref Msg17
/// @headerfile tutorial2/message/Msg17.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg17Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint32_t,
            comms::option::def::HasName,
            comms::option::def::DefaultNumValue<10>
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint32_t,
                comms::option::def::HasName,
                comms::option::def::DefaultNumValue<10>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Single special value name info entry.
        using SpecialNameInfo = tutorial2::message::Msg17FieldsCommon::F1Common::SpecialNameInfo;

        /// @brief Type returned from @ref specialNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using SpecialNamesMapInfo = tutorial2::message::Msg17FieldsCommon::F1Common::SpecialNamesMapInfo;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial2::message::Msg17FieldsCommon::F1Common::hasSpecials();
        }

        /// @brief Special value <b>"S1"</b>.
        /// @see @ref tutorial2::message::Msg17FieldsCommon::F1Common::valueS1().
        static constexpr ValueType valueS1()
        {
            return tutorial2::message::Msg17FieldsCommon::F1Common::valueS1();
        }

        /// @brief Check the value is equal to special @ref valueS1().
        bool isS1() const
        {
            return Base::getValue() == valueS1();
        }

        /// @brief Assign special value @ref valueS1() to the field.
        void setS1()
        {
            Base::setValue(valueS1());
        }

        /// @brief Retrieve map of special value names
        static SpecialNamesMapInfo specialNamesMap()
        {
            return tutorial2::message::Msg17FieldsCommon::F1Common::specialNamesMap();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg17FieldsCommon::F1Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F2 field.
    struct F2Members
    {
        /// @brief Definition of <b>"M1"</b> field.
        class M1 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::HasName
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial2::message::Msg17FieldsCommon::F2MembersCommon::M1Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg17FieldsCommon::F2MembersCommon::M1Common::name();
            }
        };

        /// @brief Definition of <b>"M2"</b> field.
        class M2 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::HasName
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial2::message::Msg17FieldsCommon::F2MembersCommon::M2Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg17FieldsCommon::F2MembersCommon::M2Common::name();
            }
        };

        /// @brief Definition of <b>"M3"</b> field.
        class M3 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::HasName
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint16_t,
                    comms::option::def::HasName
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial2::message::Msg17FieldsCommon::F2MembersCommon::M3Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg17FieldsCommon::F2MembersCommon::M3Common::name();
            }
        };

        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               M1,
               M2,
               M3
            >;
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::Bundle<
            tutorial2::field::FieldBase<>,
            typename F2Members::All,
            comms::option::def::HasName,
            comms::option::def::HasVersionDependentMembers<false>
        >
    {
        using Base =
            comms::field::Bundle<
                tutorial2::field::FieldBase<>,
                typename F2Members::All,
                comms::option::def::HasName,
                comms::option::def::HasVersionDependentMembers<false>
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated values, types and access functions are:
        ///     @li @b FieldIdx_m1 index, @b Field_m1 type and @b field_m1() access function -
        ///         for tutorial2::message::Msg17Fields::F2Members::M1 member field.
        ///     @li @b FieldIdx_m2 index, @b Field_m2 type and @b field_m2() access function -
        ///         for tutorial2::message::Msg17Fields::F2Members::M2 member field.
        ///     @li @b FieldIdx_m3 index, @b Field_m3 type and @b field_m3() access function -
        ///         for tutorial2::message::Msg17Fields::F2Members::M3 member field.
        COMMS_FIELD_MEMBERS_NAMES(
            m1,
            m2,
            m3
        );

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg17FieldsCommon::F2Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 17"</b> message class.
/// @details
///     See @ref Msg17Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg17.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg17 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M17>,
        comms::option::def::FieldsImpl<typename Msg17Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg17<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M17>,
            comms::option::def::FieldsImpl<typename Msg17Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg17<TMsgBase, TOpt> >,
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
    ///         for @ref Msg17Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg17Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 10U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 10U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg17Common::name();
    }
};

} // namespace message

} // namespace tutorial2
