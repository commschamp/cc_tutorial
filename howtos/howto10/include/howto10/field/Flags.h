// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"Flags"</b> field.

#pragma once

#include "comms/field/BitmaskValue.h"
#include "comms/options.h"
#include "howto10/field/FieldBase.h"
#include "howto10/field/FlagsCommon.h"
#include "howto10/options/DefaultOptions.h"

namespace howto10
{

namespace field
{

/// @brief Definition of <b>"Flags"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = howto10::options::DefaultOptions, typename... TExtraOpts>
class Flags : public
    comms::field::BitmaskValue<
        howto10::field::FieldBase<>,
        TExtraOpts...,
        comms::option::def::FixedLength<1U>,
        comms::option::def::BitmaskReservedBits<0xFCU, 0x0U>
    >
{
    using Base =
        comms::field::BitmaskValue<
            howto10::field::FieldBase<>,
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

    /// @brief Retrieve name of the bit.
    /// @see @ref howto10::field::FlagsCommon::bitName().
    static const char* bitName(BitIdx idx)
    {
        return
            howto10::field::FlagsCommon::bitName(
                static_cast<std::size_t>(idx));
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return howto10::field::FlagsCommon::name();
    }
};

} // namespace field

} // namespace howto10
