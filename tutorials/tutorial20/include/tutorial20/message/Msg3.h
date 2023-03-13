// Generated by commsdsl2comms v6.0.0

/// @file
/// @brief Contains definition of <b>"Message 3"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/BitmaskValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial20/MsgId.h"
#include "tutorial20/field/FieldBase.h"
#include "tutorial20/message/Msg3Common.h"
#include "tutorial20/options/DefaultOptions.h"

namespace tutorial20
{

namespace message
{

/// @brief Fields of @ref Msg3.
/// @tparam TOpt Extra options
/// @see @ref Msg3
/// @headerfile tutorial20/message/Msg3.h
template <typename TOpt = tutorial20::options::DefaultOptions>
struct Msg3Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::BitmaskValue<
            tutorial20::field::FieldBase<>,
            comms::option::def::FixedLength<1U>,
            comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
        >
    {
        using Base =
            comms::field::BitmaskValue<
                tutorial20::field::FieldBase<>,
                comms::option::def::FixedLength<1U>,
                comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
            >;
    public:
        /// @brief Provides names and generates access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        ///
        ///      The generated enum values and functions are:
        ///      @li @b BitIdx_B0, @b getBitValue_B0() and @b setBitValue_B0().
        ///      @li @b BitIdx_B1, @b getBitValue_B1() and @b setBitValue_B1().
        COMMS_BITMASK_BITS_SEQ(
            B0,
            B1
        );

        /// @brief Retrieve name of the bit.
        /// @see @ref tutorial20::message::Msg3FieldsCommon::F1Common::bitName().
        static const char* bitName(BitIdx idx)
        {
            return
                tutorial20::message::Msg3FieldsCommon::F1Common::bitName(
                    static_cast<std::size_t>(idx));
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial20::message::Msg3FieldsCommon::F1Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F2 field.
    struct F2Members
    {
        /// @brief Definition of <b>"F2"</b> field.
        class Field : public
            comms::field::IntValue<
                tutorial20::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial20::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial20::message::Msg3FieldsCommon::F2MembersCommon::FieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial20::message::Msg3FieldsCommon::F2MembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F2"</b> field.
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
            return tutorial20::message::Msg3FieldsCommon::F2Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F3 field.
    struct F3Members
    {
        /// @brief Definition of <b>"F3"</b> field.
        class Field : public
            comms::field::IntValue<
                tutorial20::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial20::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial20::message::Msg3FieldsCommon::F3MembersCommon::FieldCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial20::message::Msg3FieldsCommon::F3MembersCommon::FieldCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F3"</b> field.
    class F3 : public
        comms::field::Optional<
            typename F3Members::Field,
            comms::option::def::MissingByDefault
        >
    {
        using Base =
            comms::field::Optional<
                typename F3Members::Field,
                comms::option::def::MissingByDefault
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial20::message::Msg3FieldsCommon::F3Common::name();
        }
    };

    /// @brief Inner field of @ref F4 optional.
    class F4Field : public
        comms::field::IntValue<
            tutorial20::field::FieldBase<>,
            std::uint16_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial20::field::FieldBase<>,
                std::uint16_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial20::message::Msg3FieldsCommon::F4Common::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial20::message::Msg3FieldsCommon::F4Common::name();
        }
    };

    /// @brief Definition of version dependent
    ///     <b>F4</b> field.
    struct F4 : public
        comms::field::Optional<
            F4Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<3U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F4Field::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3,
        F4
    >;
};

/// @brief Definition of <b>"Message 3"</b> message class.
/// @details
///     See @ref Msg3Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial20/message/Msg3.h
template <typename TMsgBase, typename TOpt = tutorial20::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial20::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::HasCustomRefresh
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial20::MsgId_M3>,
            comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
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
    ///         for @ref Msg3Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg3Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg3Fields::F3 field.
    ///     @li @b FieldIdx_f4 index, @b Field_f4 type and @b field_f4() access fuction
    ///         for @ref Msg3Fields::F4 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3,
        f4
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 1U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 7U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial20::message::Msg3Common::name();
    }

    /// @brief Generated read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        Base::doFieldsVersionUpdate();
        auto es = comms::ErrorStatus::Success;
        do {
            es = Base::template doReadUntilAndUpdateLen<FieldIdx_f2>(iter, len);
            if (es != comms::ErrorStatus::Success) {
                break;
            }

            readPrepare_f2();

            es = Base::template doReadFromUntilAndUpdateLen<FieldIdx_f2, FieldIdx_f3>(iter, len);
            if (es != comms::ErrorStatus::Success) {
                break;
            }

            readPrepare_f3();

            es = Base::template doReadFrom<FieldIdx_f3>(iter, len);
        } while (false);

        return es;
    }

    /// @brief Generated refresh functionality.
    bool doRefresh()
    {
       bool updated = Base::doRefresh();
       updated = refresh_f2() || updated;
       updated = refresh_f3() || updated;
       return updated;
    }

private:
    void readPrepare_f2()
    {
        refresh_f2();
    }

    void readPrepare_f3()
    {
        refresh_f3();
    }

    bool refresh_f2()
    {
        auto mode = comms::field::OptionalMode::Missing;
        if (field_f1().getBitValue_B0()) {
            mode = comms::field::OptionalMode::Exists;
        }

        if (field_f2().getMode() == mode) {
            return false;
        }

        field_f2().setMode(mode);
        return true;
    }

    bool refresh_f3()
    {
        auto mode = comms::field::OptionalMode::Missing;
        if (field_f1().getBitValue_B1()) {
            mode = comms::field::OptionalMode::Exists;
        }

        if (field_f3().getMode() == mode) {
            return false;
        }

        field_f3().setMode(mode);
        return true;
    }
};

} // namespace message

} // namespace tutorial20
