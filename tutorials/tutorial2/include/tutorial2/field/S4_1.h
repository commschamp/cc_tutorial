// Generated by commsdsl2comms v3.5.3

/// @file
/// @brief Contains definition of <b>"S4_1"</b> field.

#pragma once

#include "comms/field/BitmaskValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/S4_1Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"S4_1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S4_1 : public
    comms::field::BitmaskValue<
        tutorial2::field::FieldBase<>,
        TExtraOpts...,
        comms::option::def::FixedLength<1U>,
        comms::option::def::BitmaskReservedBits<0xF8U, 0x0U>
    >
{
    using Base = 
        comms::field::BitmaskValue<
            tutorial2::field::FieldBase<>,
            TExtraOpts...,
            comms::option::def::FixedLength<1U>,
            comms::option::def::BitmaskReservedBits<0xF8U, 0x0U>
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
    ///      @li @b BitIdx_B2, @b getBitValue_B2() and @b setBitValue_B2().
    COMMS_BITMASK_BITS_SEQ(
        B0,
        B1,
        B2
    );
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::S4_1Common::name();
    }
    
    /// @brief Retrieve name of the bit.
    static const char* bitName(BitIdx idx)
    {
        return
            tutorial2::field::S4_1Common::bitName(
                static_cast<std::size_t>(idx));
    }
    
};

} // namespace field

} // namespace tutorial2


