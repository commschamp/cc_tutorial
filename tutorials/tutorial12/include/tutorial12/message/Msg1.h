// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial12/MsgId.h"
#include "tutorial12/field/FieldBase.h"
#include "tutorial12/field/Length.h"
#include "tutorial12/message/Msg1Common.h"
#include "tutorial12/options/DefaultOptions.h"


namespace tutorial12
{

namespace message
{


/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile tutorial12/message/Msg1.h
template <typename TOpt = tutorial12::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
        comms::field::String<
            tutorial12::field::FieldBase<>,
            typename TOpt::message::Msg1Fields::F1,
            comms::option::def::SequenceSerLengthFieldPrefix<tutorial12::field::Length<TOpt> >
        >
    {
        using Base =
            comms::field::String<
                tutorial12::field::FieldBase<>,
                typename TOpt::message::Msg1Fields::F1,
                comms::option::def::SequenceSerLengthFieldPrefix<tutorial12::field::Length<TOpt> >
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial12::message::Msg1FieldsCommon::F1Common::name();
        }
        
    
    };
    
    
    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::String<
            tutorial12::field::FieldBase<>,
            typename TOpt::message::Msg1Fields::F2,
            comms::option::def::SequenceFixedSize<8U>
        >
    {
        using Base =
            comms::field::String<
                tutorial12::field::FieldBase<>,
                typename TOpt::message::Msg1Fields::F2,
                comms::option::def::SequenceFixedSize<8U>
            >;
    public:
        /// @brief Default constructor
        F2()
        {
            static const char Str[] = "hello";
            static const std::size_t StrSize = std::extent<decltype(Str)>::value;
            Base::setValue(typename Base::ValueType(&Str[0], StrSize - 1));
        }
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial12::message::Msg1FieldsCommon::F2Common::name();
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
/// @headerfile tutorial12/message/Msg1.h
template <typename TMsgBase, typename TOpt = tutorial12::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial12::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial12::MsgId_M1>,
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
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg1Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg1Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static_assert(MsgMinLen == 9U, "Unexpected min serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial12::message::Msg1Common::name();
    }
    

};

} // namespace message

} // namespace tutorial12


