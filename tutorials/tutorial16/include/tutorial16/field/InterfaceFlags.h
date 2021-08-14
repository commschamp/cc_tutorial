// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of <b>"InterfaceFlags"</b> field.

#pragma once

#include "comms/field/BitmaskValue.h"
#include "comms/options.h"
#include "tutorial16/field/FieldBase.h"
#include "tutorial16/field/InterfaceFlagsCommon.h"
#include "tutorial16/options/DefaultOptions.h"

namespace tutorial16
{

namespace field
{

/// @brief Definition of <b>"InterfaceFlags"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial16::options::DefaultOptions, typename... TExtraOpts>
class InterfaceFlags : public
    comms::field::BitmaskValue<
        tutorial16::field::FieldBase<>,
        TExtraOpts...,
        comms::option::def::FixedLength<1U>,
        comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
    >
{
    using Base = 
        comms::field::BitmaskValue<
            tutorial16::field::FieldBase<>,
            TExtraOpts...,
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
        return tutorial16::field::InterfaceFlagsCommon::name();
    }
    
    /// @brief Retrieve name of the bit.
    static const char* bitName(BitIdx idx)
    {
        return
            tutorial16::field::InterfaceFlagsCommon::bitName(
                static_cast<std::size_t>(idx));
    }
    
};

} // namespace field

} // namespace tutorial16


