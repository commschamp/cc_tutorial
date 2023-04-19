// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"S1"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "t23_ext/field/FieldBase.h"
#include "t23_ext/ns1/field/S1Common.h"
#include "t23_ext/options/DefaultOptions.h"

namespace t23_ext
{

namespace ns1
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref S1 field.
/// @tparam TOpt Protocol options.
template <typename TOpt = t23_ext::options::DefaultOptions>
struct S1Members
{
    /// @brief Definition of <b>"LengthPrefix"</b> field.
    class LengthPrefix : public
        comms::field::IntValue<
            t23_ext::field::FieldBase<>,
            std::uint8_t
        >
    {
        using Base =
            comms::field::IntValue<
                t23_ext::field::FieldBase<>,
                std::uint8_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return t23_ext::ns1::field::S1MembersCommon::LengthPrefixCommon::hasSpecials();
        }

        /// @brief Name of the field.
        static const char* name()
        {
            return t23_ext::ns1::field::S1MembersCommon::LengthPrefixCommon::name();
        }
    };
};

/// @brief Definition of <b>"S1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = t23_ext::options::DefaultOptions, typename... TExtraOpts>
class S1 : public
    comms::field::String<
        t23_ext::field::FieldBase<>,
        TExtraOpts...,
        typename TOpt::t23_ext::ns1::field::S1,
        comms::option::def::SequenceSerLengthFieldPrefix<typename S1Members<TOpt>::LengthPrefix>
    >
{
    using Base =
        comms::field::String<
            t23_ext::field::FieldBase<>,
            TExtraOpts...,
            typename TOpt::t23_ext::ns1::field::S1,
            comms::option::def::SequenceSerLengthFieldPrefix<typename S1Members<TOpt>::LengthPrefix>
        >;
public:
    /// @brief Name of the field.
    static const char* name()
    {
        return t23_ext::ns1::field::S1Common::name();
    }
};

} // namespace field

} // namespace ns1

} // namespace t23_ext
