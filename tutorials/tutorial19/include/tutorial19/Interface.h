// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"Interface"</b> interface class.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/Message.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial19/InterfaceCommon.h"
#include "tutorial19/MsgId.h"
#include "tutorial19/field/FieldBase.h"

namespace tutorial19
{

/// @brief Extra transport fields of @ref Interface interface class.
/// @see @ref Interface
/// @headerfile "tutorial19/Interface.h"
struct InterfaceFields
{
    /// @brief Definition of <b>"Version"</b> field.
    struct Version : public
        comms::field::IntValue<
            tutorial19::field::FieldBase<>,
            std::uint16_t,
            comms::option::def::DefaultNumValue<5U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial19::InterfaceFieldsCommon::VersionCommon::name();
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Version
    >;
};

/// @brief Definition of <b>"Interface"</b> common interface class.
/// @details Common Interface for all the messages.
/// @tparam TOpt Interface definition options
/// @headerfile "tutorial19/Interface.h"
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial19::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>,
        comms::option::def::VersionInExtraTransportFields<0U>
    >
{
    using Base =
        comms::Message<
            TOpt...,
            comms::option::def::BigEndian,
            comms::option::def::MsgIdType<tutorial19::MsgId>,
            comms::option::def::ExtraTransportFields<InterfaceFields::All>,
            comms::option::def::VersionInExtraTransportFields<0U>
        >;
public:
    /// @brief Allow access to extra transport fields.
    /// @details See definition of @b COMMS_MSG_TRANSPORT_FIELDS_NAMES macro
    ///     related to @b comms::Message class from COMMS library
    ///     for details.
    ///
    ///     The generated functions are:
    ///     @li @b TransportField_version type and @b transportField_version() function for
    ///         @ref InterfaceFields::Version field.
    COMMS_MSG_TRANSPORT_FIELDS_NAMES(
        version
    );
};

} // namespace tutorial19


