// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"Interface"</b> interface class.

#pragma once

#include <tuple>
#include "comms/Message.h"
#include "comms/field/BitmaskValue.h"
#include "comms/options.h"
#include "tutorial17/InterfaceCommon.h"
#include "tutorial17/MsgId.h"
#include "tutorial17/field/FieldBase.h"

namespace tutorial17
{

/// @brief Extra transport fields of @ref Interface interface class.
/// @see @ref Interface
/// @headerfile "tutorial17/Interface.h"
struct InterfaceFields
{
    /// @brief Definition of <b>"Flags"</b> field.
    class Flags : public
        comms::field::BitmaskValue<
            tutorial17::field::FieldBase<>,
            comms::option::def::FixedLength<1U>,
            comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
        >
    {
        using Base = 
            comms::field::BitmaskValue<
                tutorial17::field::FieldBase<>,
                comms::option::def::FixedLength<1U>,
                comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
            >;
    public:
        /// @brief Provides names and generates access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        ///
        ///      The generated enum values and functions are:
        ///      @li @b BitIdx_B0, @b getBitValue_B0() and @b setBitValue_B0().
        ///      @li @b BitIdx_B1, @b getBitValue_B1() and @b setBitValue_B1().
        COMMS_BITMASK_BITS_SEQ(
            B0,
            B1
        );
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial17::InterfaceFieldsCommon::FlagsCommon::name();
        }
        
        /// @brief Retrieve name of the bit.
        static const char* bitName(BitIdx idx)
        {
            return
                tutorial17::InterfaceFieldsCommon::FlagsCommon::bitName(
                    static_cast<std::size_t>(idx));
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Flags
    >;
};

/// @brief Definition of <b>"Interface"</b> common interface class.
/// @details Common Interface for all the messages.
/// @tparam TOpt Interface definition options
/// @headerfile "tutorial17/Interface.h"
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial17::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>
    >
{
    using Base =
        comms::Message<
            TOpt...,
            comms::option::def::BigEndian,
            comms::option::def::MsgIdType<tutorial17::MsgId>,
            comms::option::def::ExtraTransportFields<InterfaceFields::All>
        >;
public:
    /// @brief Allow access to extra transport fields.
    /// @details See definition of @b COMMS_MSG_TRANSPORT_FIELDS_NAMES macro
    ///     related to @b comms::Message class from COMMS library
    ///     for details.
    ///
    ///     The generated functions are:
    ///     @li @b TransportField_flags type and @b transportField_flags() function for
    ///         @ref InterfaceFields::Flags field.
    COMMS_MSG_TRANSPORT_FIELDS_NAMES(
        flags
    );
};

} // namespace tutorial17


