// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains definition of <b>"Msg1Flags"</b> field.

#pragma once

#include "comms/field/BitmaskValue.h"
#include "comms/options.h"
#include "tutorial21/field/FieldBase.h"
#include "tutorial21/field/Msg1FlagsCommon.h"
#include "tutorial21/options/DefaultOptions.h"

namespace tutorial21
{

namespace field
{

/// @brief Definition of <b>"Msg1Flags"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial21::options::DefaultOptions, typename... TExtraOpts>
class Msg1Flags : public
    comms::field::BitmaskValue<
        tutorial21::field::FieldBase<>,
        TExtraOpts...,
        comms::option::def::FixedLength<1U>,
        comms::option::def::BitmaskReservedBits<0xF8U, 0x0U>
    >
{
    using Base =
        comms::field::BitmaskValue<
            tutorial21::field::FieldBase<>,
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

    /// @brief Retrieve name of the bit.
    /// @see @ref tutorial21::field::Msg1FlagsCommon::bitName().
    static const char* bitName(BitIdx idx)
    {
        return
            tutorial21::field::Msg1FlagsCommon::bitName(
                static_cast<std::size_t>(idx));
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial21::field::Msg1FlagsCommon::name();
    }
};

} // namespace field

} // namespace tutorial21
