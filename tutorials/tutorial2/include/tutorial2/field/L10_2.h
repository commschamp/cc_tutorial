// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"L10_2"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/ArrayList.h"
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/L10_2Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref L10_2 list.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct L10_2Members
{
    /// @brief Definition of <b>"Element"</b> field.
    struct Element : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::int16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_2MembersCommon::ElementCommon::name();
        }
        
    };
    
    /// @brief Definition of <b>"Size"</b> field.
    struct Size : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint32_t,
            comms::option::def::VarLength<1U, 4U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_2MembersCommon::SizeCommon::name();
        }
        
    };
    
};

/// @brief Definition of <b>"L10_2"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
struct L10_2 : public
    comms::field::ArrayList<
        tutorial2::field::FieldBase<>,
        typename L10_2Members<TOpt>::Element,
        TExtraOpts...,
        typename TOpt::field::L10_2,
        comms::option::def::SequenceSizeFieldPrefix<typename L10_2Members<TOpt>::Size>
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::L10_2Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2


