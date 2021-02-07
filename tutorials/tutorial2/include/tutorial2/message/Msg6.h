// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"Message 6"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/S6_1.h"
#include "tutorial2/field/S6_2.h"
#include "tutorial2/field/S6_3.h"
#include "tutorial2/field/S6_4.h"
#include "tutorial2/message/Msg6Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace message
{

/// @brief Fields of @ref Msg6.
/// @tparam TOpt Extra options
/// @see @ref Msg6
/// @headerfile "tutorial2/message/Msg6.h"
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg6Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        tutorial2::field::S6_1<
            TOpt
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg6FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"F2"</b> field.
    struct F2 : public
        tutorial2::field::S6_2<
            TOpt
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg6FieldsCommon::F2Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"F3"</b> field.
    struct F3 : public
        tutorial2::field::S6_3<
            TOpt
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg6FieldsCommon::F3Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"F4"</b> field.
    struct F4 : public
        tutorial2::field::S6_4<
            TOpt
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg6FieldsCommon::F4Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"F5"</b> field.
    struct F5 : public
        comms::field::String<
            tutorial2::field::FieldBase<>,
            typename TOpt::message::Msg6Fields::F5
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg6FieldsCommon::F5Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3,
        F4,
        F5
    >;
};

/// @brief Definition of <b>"Message 6"</b> message class.
/// @details
///     See @ref Msg6Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial2/message/Msg6.h"
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg6 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M6>,
        comms::option::def::FieldsImpl<typename Msg6Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg6<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M6>,
            comms::option::def::FieldsImpl<typename Msg6Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg6<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated types and functions are:
    ///     @li @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg6Fields::F1 field.
    ///     @li @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg6Fields::F2 field.
    ///     @li @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg6Fields::F3 field.
    ///     @li @b Field_f4 type and @b field_f4() access fuction
    ///         for @ref Msg6Fields::F4 field.
    ///     @li @b Field_f5 type and @b field_f5() access fuction
    ///         for @ref Msg6Fields::F5 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3,
        f4,
        f5
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 8U, "Unexpected min serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg6Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial2


