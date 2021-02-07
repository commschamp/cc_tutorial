// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"Message 3"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/ArrayList.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial12/MsgId.h"
#include "tutorial12/field/FieldBase.h"
#include "tutorial12/field/Length.h"
#include "tutorial12/message/Msg3Common.h"
#include "tutorial12/options/DefaultOptions.h"

namespace tutorial12
{

namespace message
{

/// @brief Fields of @ref Msg3.
/// @tparam TOpt Extra options
/// @see @ref Msg3
/// @headerfile "tutorial12/message/Msg3.h"
template <typename TOpt = tutorial12::options::DefaultOptions>
struct Msg3Fields
{
    /// @brief Scope for all the member fields of
    ///     @ref F1 list.
    struct F1Members
    {
        /// @brief Definition of <b>"Element"</b> field.
        struct Element : public
            comms::field::IntValue<
                tutorial12::field::FieldBase<>,
                std::uint32_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial12::message::Msg3FieldsCommon::F1MembersCommon::ElementCommon::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::ArrayList<
            tutorial12::field::FieldBase<>,
            typename F1Members::Element,
            typename TOpt::message::Msg3Fields::F1,
            comms::option::def::SequenceSizeFieldPrefix<tutorial12::field::Length<TOpt> >
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial12::message::Msg3FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief Scope for all the member fields of
    ///     @ref F2 list.
    struct F2Members
    {
        /// @brief Definition of <b>"Element"</b> field.
        struct Element : public
            comms::field::IntValue<
                tutorial12::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial12::message::Msg3FieldsCommon::F2MembersCommon::ElementCommon::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F2"</b> field.
    struct F2 : public
        comms::field::ArrayList<
            tutorial12::field::FieldBase<>,
            typename F2Members::Element,
            typename TOpt::message::Msg3Fields::F2,
            comms::option::def::SequenceFixedSize<6U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial12::message::Msg3FieldsCommon::F2Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 3"</b> message class.
/// @details
///     See @ref Msg3Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial12/message/Msg3.h"
template <typename TMsgBase, typename TOpt = tutorial12::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial12::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial12::MsgId_M3>,
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
    ///     The generated types and functions are:
    ///     @li @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg3Fields::F1 field.
    ///     @li @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg3Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 13U, "Unexpected min serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial12::message::Msg3Common::name();
    }
    
    
};

} // namespace message

} // namespace tutorial12


