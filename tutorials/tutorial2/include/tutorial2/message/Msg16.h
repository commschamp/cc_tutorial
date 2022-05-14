// Generated by commsdsl2comms v4.0.0

/// @file
/// @brief Contains definition of <b>"Message 16"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/MsgId.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/message/Msg16Common.h"
#include "tutorial2/options/DefaultOptions.h"


namespace tutorial2
{

namespace message
{


/// @brief Fields of @ref Msg16.
/// @tparam TOpt Extra options
/// @see @ref Msg16
/// @headerfile tutorial2/message/Msg16.h
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg16Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    class F1 : public
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
            return tutorial2::message::Msg16FieldsCommon::F1Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg16FieldsCommon::F1Common::name();
        }
        
    
    };
    
    
    /// @brief Definition of <b>"F2"</b> field.
    class F2 : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::int8_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::int8_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial2::message::Msg16FieldsCommon::F2Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg16FieldsCommon::F2Common::name();
        }
        
    
    };
    
    
    /// @brief Definition of <b>"F3"</b> field.
    class F3 : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::int8_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::int8_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial2::message::Msg16FieldsCommon::F3Common::hasSpecials();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::message::Msg16FieldsCommon::F3Common::name();
        }
        
    
    };
    
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 16"</b> message class.
/// @details
///     See @ref Msg16Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial2/message/Msg16.h
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg16 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M16>,
        comms::option::def::FieldsImpl<typename Msg16Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg16<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial2::MsgId_M16>,
            comms::option::def::FieldsImpl<typename Msg16Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg16<TMsgBase, TOpt> >,
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
    ///         for @ref Msg16Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg16Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg16Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 3U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 3U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial2::message::Msg16Common::name();
    }
    

};

} // namespace message

} // namespace tutorial2


