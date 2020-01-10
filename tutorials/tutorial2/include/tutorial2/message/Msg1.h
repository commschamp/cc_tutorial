// Generated by commsdsl2comms v3.3.0

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/I1.h"
#include "tutorial2/message/Msg1Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile "tutorial2/message/Msg1.h"
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        tutorial2::field::I1<
            TOpt
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg1FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"F2"</b> field.
    struct F2 : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::int16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg1FieldsCommon::F2Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial2/message/Msg1.h"
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M1>,
            comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Field_f1 type and @b field_f1() fuction
    ///         for @ref Msg1Fields::F1 field.
    ///     @li @b Field_f2 type and @b field_f2() fuction
    ///         for @ref Msg1Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 3U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 3U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg1Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial2


