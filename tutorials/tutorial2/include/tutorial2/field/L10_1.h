// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains definition of <b>"L10_1"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/ArrayList.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/L10_1Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref L10_1 field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct L10_1Members
{
    /// @brief Definition of <b>"Element"</b> field.
    class Element : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint32_t,
            comms::option::def::HasName
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint32_t,
                comms::option::def::HasName
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial2::field::L10_1MembersCommon::ElementCommon::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_1MembersCommon::ElementCommon::name();
        }
    };
};

/// @brief Definition of <b>"L10_1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class L10_1 : public
    comms::field::ArrayList<
        tutorial2::field::FieldBase<>,
        typename L10_1Members<TOpt>::Element,
        TExtraOpts...,
        typename TOpt::field::L10_1,
        comms::option::def::HasName,
        comms::option::def::SequenceFixedSize<5U>
    >
{
    using Base =
        comms::field::ArrayList<
            tutorial2::field::FieldBase<>,
            typename L10_1Members<TOpt>::Element,
            TExtraOpts...,
            typename TOpt::field::L10_1,
            comms::option::def::HasName,
            comms::option::def::SequenceFixedSize<5U>
        >;
public:
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::L10_1Common::name();
    }
};

} // namespace field

} // namespace tutorial2
