// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"Interface"</b> interface class.

#pragma once

#include <tuple>
#include "comms/Message.h"
#include "comms/options.h"
#include "tutorial21/InterfaceCommon.h"
#include "tutorial21/MsgId.h"
#include "tutorial21/field/BasicFlags.h"
#include "tutorial21/field/FieldBase.h"

namespace tutorial21
{

/// @brief Extra transport fields of @ref Interface interface class.
/// @see @ref Interface
/// @headerfile tutorial21/Interface.h
struct InterfaceFields
{
    /// @brief Definition of <b>"Flags"</b> field.
    using Flags =
        tutorial21::field::BasicFlags<
            tutorial21::options::DefaultOptions,
            comms::option::def::HasName
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Flags
    >;
};

/// @brief Definition of <b>"Interface"</b> common interface class.
/// .incCommon Interface for all the messages. @n
/// @tparam TOpt Interface definition options
/// @headerfile tutorial21/Interface.h
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial21::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>
    >
{
    using Base =
        comms::Message<
            TOpt...,
            comms::option::def::BigEndian,
            comms::option::def::MsgIdType<tutorial21::MsgId>,
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

} // namespace tutorial21
