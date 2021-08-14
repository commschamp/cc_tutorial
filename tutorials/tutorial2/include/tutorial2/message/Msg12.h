// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of <b>"Message 12"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg12Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg12.
/// @tparam TOpt Extra options
/// @see @ref Msg12
/// @headerfile "tutorial2/message/Msg12.h"
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg12Fields
{
    /// @brief Scope for all the member fields of
    ///     @ref F1 optional.
    struct F1Members
    {
        /// @brief Definition of <b>"ActF1"</b> field.
        struct ActF1 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::message::Msg12FieldsCommon::F1MembersCommon::ActF1Common::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::Optional<
            typename F1Members::ActF1
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg12FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 12"</b> message class.
/// @details
///     See @ref Msg12Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial2/message/Msg12.h"
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg12 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M12>,
        comms::option::def::FieldsImpl<typename Msg12Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg12<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M12>,
            comms::option::def::FieldsImpl<typename Msg12Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg12<TMsgBase, TOpt> >,
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
    ///         for @ref Msg12Fields::F1 field.
    COMMS_MSG_FIELDS_NAMES(
        f1
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 0U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg12Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial2


