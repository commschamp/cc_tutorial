// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of <b>"D7_2"</b> field.

#pragma once

#include <cstdint>
#include <iterator>
#include "comms/field/ArrayList.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/util/assign.h"
#include "tutorial2/field/D7_2Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref D7_2 field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct D7_2Members
{
    /// @brief Definition of <b>"Length"</b> field.
    class Length : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint8_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint8_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial2::field::D7_2MembersCommon::LengthCommon::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::D7_2MembersCommon::LengthCommon::name();
        }
    };
};

/// @brief Definition of <b>"D7_2"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class D7_2 : public
    comms::field::ArrayList<
        tutorial2::field::FieldBase<>,
        std::uint8_t,
        TExtraOpts...,
        typename TOpt::field::D7_2,
        comms::option::def::SequenceSerLengthFieldPrefix<typename D7_2Members<TOpt>::Length>
    >
{
    using Base =
        comms::field::ArrayList<
            tutorial2::field::FieldBase<>,
            std::uint8_t,
            TExtraOpts...,
            typename TOpt::field::D7_2,
            comms::option::def::SequenceSerLengthFieldPrefix<typename D7_2Members<TOpt>::Length>
        >;
public:
    /// @brief Default constructor
    D7_2()
    {
        static const std::uint8_t Data[] = {
            0xab, 0xcd, 0xef, 0x01, 0x23, 0x45
        };
        comms::util::assign(Base::value(), std::begin(Data), std::end(Data));
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::D7_2Common::name();
    }
};

} // namespace field

} // namespace tutorial2
