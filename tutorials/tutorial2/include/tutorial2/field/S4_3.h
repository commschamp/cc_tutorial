// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of <b>"S4_3"</b> field.

#pragma once

#include "comms/field/BitmaskValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/S4_3Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"S4_3"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S4_3 : public
    comms::field::BitmaskValue<
        tutorial2::field::FieldBase<>,
        TExtraOpts...,
        comms::option::def::FixedLength<3U>,
        comms::option::def::DefaultNumValue<0x1U>,
        comms::option::def::BitmaskReservedBits<0xEFFFDEUL, 0xEFFFDCUL>
    >
{
    using Base =
        comms::field::BitmaskValue<
            tutorial2::field::FieldBase<>,
            TExtraOpts...,
            comms::option::def::FixedLength<3U>,
            comms::option::def::DefaultNumValue<0x1U>,
            comms::option::def::BitmaskReservedBits<0xEFFFDEUL, 0xEFFFDCUL>
        >;
public:
    /// @brief Provide names for internal bits.
    /// @details See definition of @b COMMS_BITMASK_BITS macro
    ///     related to @b comms::field::BitmaskValue class from COMMS library
    ///     for details.
    ///
    ///      The generated enum values:
    ///      @li @b BitIdx_B0.
    ///      @li @b BitIdx_B1.
    ///      @li @b BitIdx_B5.
    ///      @li @b BitIdx_B20.
    COMMS_BITMASK_BITS(
        B0=0,
        B1=1,
        B5=5,
        B20=20
    );

    /// @brief Generates independent access functions for internal bits.
    /// @details See definition of @b COMMS_BITMASK_BITS_ACCESS macro
    ///     related to @b comms::field::BitmaskValue class from COMMS library
    ///     for details.
    ///
    ///     The generated access functions are:
    ///      @li @b getBitValue_B0() and @b setBitValue_B0().
    ///      @li @b getBitValue_B1() and @b setBitValue_B1().
    ///      @li @b getBitValue_B5() and @b setBitValue_B5().
    ///      @li @b getBitValue_B20() and @b setBitValue_B20().
    COMMS_BITMASK_BITS_ACCESS(
        B0,
        B1,
        B5,
        B20
    );

    /// @brief Retrieve name of the bit.
    /// @see @ref tutorial2::field::S4_3Common::bitName().
    static const char* bitName(BitIdx idx)
    {
        return
            tutorial2::field::S4_3Common::bitName(
                static_cast<std::size_t>(idx));
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::S4_3Common::name();
    }
};

} // namespace field

} // namespace tutorial2
