// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains definition of <b>"Interface"</b> interface class.

#pragma once

#include <tuple>
#include "comms/Message.h"
#include "comms/options.h"
#include "tutorial20/InterfaceCommon.h"
#include "tutorial20/MsgId.h"
#include "tutorial20/field/FieldBase.h"
#include "tutorial20/field/Version.h"

namespace tutorial20
{

/// @brief Extra transport fields of @ref Interface interface class.
/// @see @ref Interface
/// @headerfile tutorial20/Interface.h
struct InterfaceFields
{
    /// @brief Definition of <b>"Version"</b> field.
    using Version =
        tutorial20::field::Version<
            tutorial20::options::DefaultOptions
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Version
    >;
};

/// @brief Definition of <b>"Interface"</b> common interface class.
/// .incCommon Interface for all the messages. @n
/// @tparam TOpt Interface definition options
/// @headerfile tutorial20/Interface.h
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial20::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>,
        comms::option::def::VersionInExtraTransportFields<0U>
    >
{
    using Base =
        comms::Message<
            TOpt...,
            comms::option::def::BigEndian,
            comms::option::def::MsgIdType<tutorial20::MsgId>,
            comms::option::def::ExtraTransportFields<InterfaceFields::All>,
            comms::option::def::VersionInExtraTransportFields<0U>
        >;
public:
    /// @brief Allow access to extra transport fields.
    /// @details See definition of @b COMMS_MSG_TRANSPORT_FIELDS_NAMES macro
    ///     related to @b comms::Message class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b TransportFieldIdx_version index, @b TransportField_version type
    ///         and @b transportField_version() access fuction for @ref InterfaceFields::Version field.
    COMMS_MSG_TRANSPORT_FIELDS_NAMES(
        version
    );
};

} // namespace tutorial20
