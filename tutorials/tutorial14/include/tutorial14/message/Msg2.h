// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial14/MsgId.h"
#include "tutorial14/field/FieldBase.h"
#include "tutorial14/message/Msg2Common.h"
#include "tutorial14/options/DefaultOptions.h"
#include <iostream>

namespace tutorial14
{

namespace message
{

/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile "tutorial14/message/Msg2.h"
template <typename TOpt = tutorial14::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::IntValue<
            tutorial14::field::FieldBase<>,
            std::uint16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial14::message::Msg2FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1
    >;
};

/// @brief Definition of <b>"Message 2"</b> message class.
/// @details
///     See @ref Msg2Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial14/message/Msg2.h"
template <typename TMsgBase, typename TOpt = tutorial14::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial14::MsgId_M2>,
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
            comms::option::def::StaticNumIdImpl<tutorial14::MsgId_M2>,
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
    ///     The generated types and functions are:
    ///     @li @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg2Fields::F1 field.
    COMMS_MSG_FIELDS_NAMES(
        f1
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");
    
    
    // Custom code added to the public section
    
    /// @brief Custom name retrieval
    static const char* doName()
    {
        return "Custom Message2";
    }
    
    /// @brief Custom read 
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        std::cout << "Call of custom " << __FUNCTION__ << std::endl;
        return Base::doRead(iter, len);
    }
    
    /// @brief Custom write 
    template <typename TIter>
    comms::ErrorStatus doWrite(TIter& iter, std::size_t len) const
    {
        std::cout << "Call of custom " << __FUNCTION__ << std::endl;
        return Base::doWrite(iter, len);
    }
    
    /// @brief Custom length calculation
    std::size_t doLength() const
    {
        std::cout << "Call of custom " << __FUNCTION__ << std::endl;
        return Base::doLength();
    }
    
    /// @brief Custom validity check
    bool doValid() const
    {
        std::cout << "Call of custom " << __FUNCTION__ << std::endl;
        return Base::doValid();
    }
    
    /// @brief Custom refresh
    bool doRefresh()
    {
        std::cout << "Call of custom " << __FUNCTION__ << std::endl;
        return Base::doRefresh();
    }
    
    
protected:
    // Custom code added to the protected section
    
private:
    // Custom code added to the private section
    
};

} // namespace message

} // namespace tutorial14


// Custom code added to the end of the file

