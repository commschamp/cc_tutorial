// Generated by commsdsl2comms v3.8.0

/// @file
/// @brief Contains definition of <b>"Interface"</b> interface class.

#pragma once

#include <tuple>
#include "comms/Message.h"
#include "comms/options.h"
#include "howto1/InterfaceCommon.h"
#include "howto1/MsgId.h"
#include "howto1/field/FieldBase.h"
#include "howto1/field/InterfaceFlags.h"

namespace howto1
{


/// @brief Extra transport fields of @ref Interface interface class.
/// @see @ref Interface
/// @headerfile howto1/Interface.h
struct InterfaceFields
{
    /// @brief Definition of <b>"Flags"</b> field.
    class Flags : public
        howto1::field::InterfaceFlags<
            howto1::options::DefaultOptions
        >
    {
        using Base =
            howto1::field::InterfaceFlags<
                howto1::options::DefaultOptions
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return howto1::InterfaceFieldsCommon::FlagsCommon::name();
        }
        
    
    };
    
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Flags
    >;
};

/// @brief Definition of <b>"Interface"</b> common interface class.
/// .incCommon Interface for all the messages. @n
/// @tparam TOpt Interface definition options
/// @headerfile howto1/Interface.h
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<howto1::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>
    >
{
    using Base =
        comms::Message<
            TOpt...,
            comms::option::def::BigEndian,
            comms::option::def::MsgIdType<howto1::MsgId>,
            comms::option::def::ExtraTransportFields<InterfaceFields::All>
        >;
public:
    /// @brief Allow access to extra transport fields.
    /// @details See definition of @b COMMS_MSG_TRANSPORT_FIELDS_NAMES macro
    ///     related to @b comms::Message class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b TransportFieldIdx_flags index, @b TransportField_flags type
    ///         and @b transportField_flags() access fuction for @ref InterfaceFields::Flags field.
    COMMS_MSG_TRANSPORT_FIELDS_NAMES(
        flags
    );
    

};

} // namespace howto1


