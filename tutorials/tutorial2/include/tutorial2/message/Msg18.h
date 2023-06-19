// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"Message 18"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg18Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg18.
/// @tparam TOpt Extra options
/// @see @ref Msg18
/// @headerfile tutorial2/message/Msg18.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg18Fields
{
    /// @brief Scope for all the member fields of
    ///     @ref F1 field.
    struct F1Members
    {
        /// @brief Definition of <b>"Length"</b> field.
        class Length : public
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
                return tutorial2::message::Msg18FieldsCommon::F1MembersCommon::LengthCommon::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg18FieldsCommon::F1MembersCommon::LengthCommon::name();
            }
        };
    };

    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::String<
            tutorial2::field::FieldBase<>,
            typename TOpt::message::Msg18Fields::F1,
            comms::option::def::SequenceSerLengthFieldPrefix<typename F1Members::Length>
        >
    {
        using Base =
            comms::field::String<
                tutorial2::field::FieldBase<>,
                typename TOpt::message::Msg18Fields::F1,
                comms::option::def::SequenceSerLengthFieldPrefix<typename F1Members::Length>
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg18FieldsCommon::F1Common::name();
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
                return tutorial2::message::Msg18FieldsCommon::F2MembersCommon::ActF2Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg18FieldsCommon::F2MembersCommon::ActF2Common::name();
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
            return tutorial2::message::Msg18FieldsCommon::F2Common::name();
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
                return tutorial2::message::Msg18FieldsCommon::F3MembersCommon::ActF3Common::hasSpecials();
            }

            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg18FieldsCommon::F3MembersCommon::ActF3Common::name();
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
            return tutorial2::message::Msg18FieldsCommon::F3Common::name();
        }
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 18"</b> message class.
/// @details
///     See @ref Msg18Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg18.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg18 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M18>,
        comms::option::def::FieldsImpl<typename Msg18Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg18<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::HasCustomRefresh
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M18>,
            comms::option::def::FieldsImpl<typename Msg18Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg18<TMsgBase, TOpt> >,
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
    ///         for @ref Msg18Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg18Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg18Fields::F3 field.
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
        return tutorial2::message::Msg18Common::name();
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
        if (!field_f1().getValue().empty()) {
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
        if (!(field_f2().doesExist())) {
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
