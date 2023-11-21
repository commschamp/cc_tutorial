// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains definition of <b>"Message 13"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/BitmaskValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg13Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg13.
/// @tparam TOpt Extra options
/// @see @ref Msg13
/// @headerfile tutorial2/message/Msg13.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg13Fields
{
    /// @brief Definition of <b>"Flags"</b> field.
    class Flags : public
        comms::field::BitmaskValue<
            tutorial2::field::FieldBase<>,
            comms::option::def::FixedLength<1U>,
            comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
        >
    {
        using Base =
            comms::field::BitmaskValue<
                tutorial2::field::FieldBase<>,
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
        ///      @li @b BitIdx_F2Present, @b getBitValue_F2Present() and @b setBitValue_F2Present().
        ///      @li @b BitIdx_F3Missing, @b getBitValue_F3Missing() and @b setBitValue_F3Missing().
        COMMS_BITMASK_BITS_SEQ(
            F2Present,
            F3Missing
        );

        /// @brief Retrieve name of the bit.
        /// @see @ref tutorial2::message::Msg13FieldsCommon::FlagsCommon::bitName().
        static const char* bitName(BitIdx idx)
        {
            return
                tutorial2::message::Msg13FieldsCommon::FlagsCommon::bitName(
                    static_cast<std::size_t>(idx));
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg13FieldsCommon::FlagsCommon::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F2 field.
    struct F2Members
    {
        /// @brief Definition of <b>"ActF2"</b> field.
        class ActF2 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial2::message::Msg13FieldsCommon::F2MembersCommon::ActF2Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg13FieldsCommon::F2MembersCommon::ActF2Common::name();
            }
        };
    };

    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::Optional<
            typename F2Members::ActF2,
            comms::option::def::MissingByDefault
        >
    {
        using Base =
            comms::field::Optional<
                typename F2Members::ActF2,
                comms::option::def::MissingByDefault
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg13FieldsCommon::F2Common::name();
        }
    };

    /// @brief Scope for all the member fields of
    ///     @ref F3 field.
    struct F3Members
    {
        /// @brief Definition of <b>"ActF3"</b> field.
        class ActF3 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint8_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial2::field::FieldBase<>,
                    std::uint8_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial2::message::Msg13FieldsCommon::F3MembersCommon::ActF3Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg13FieldsCommon::F3MembersCommon::ActF3Common::name();
            }
        };
    };

    /// @brief Definition of <b>"F3"</b> field.
    class F3 : public
        comms::field::Optional<
            typename F3Members::ActF3,
            comms::option::def::ExistsByDefault
        >
    {
        using Base =
            comms::field::Optional<
                typename F3Members::ActF3,
                comms::option::def::ExistsByDefault
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg13FieldsCommon::F3Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Flags,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 13"</b> message class.
/// @details
///     See @ref Msg13Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg13.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg13 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M13>,
        comms::option::def::FieldsImpl<typename Msg13Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg13<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::HasCustomRefresh
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M13>,
            comms::option::def::FieldsImpl<typename Msg13Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg13<TMsgBase, TOpt> >,
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
    ///     @li @b FieldIdx_flags index, @b Field_flags type and @b field_flags() access fuction
    ///         for @ref Msg13Fields::Flags field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg13Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg13Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        flags,
        f2,
        f3
    );

    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 1U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 4U, "Unexpected max serialisation length");

    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg13Common::name();
    }

    /// @brief Generated read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
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
        if (field_flags().getBitValue_F2Present()) {
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
        if (!field_flags().getBitValue_F3Missing()) {
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

} // namespace tutorial2
