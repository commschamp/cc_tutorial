// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"S6_2"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/S6_2Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref S6_2 string.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct S6_2Members
{
    /// @brief Definition of <b>"Length"</b> field.
    struct Length : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint8_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::S6_2MembersCommon::LengthCommon::name();
        }
        
    };
    
};

/// @brief Definition of <b>"S6_2"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S6_2 : public
    comms::field::String<
        tutorial2::field::FieldBase<>,
        TExtraOpts...,
        typename TOpt::field::S6_2,
        comms::option::def::SequenceSerLengthFieldPrefix<typename S6_2Members<TOpt>::Length>
    >
{
    using Base = 
        comms::field::String<
            tutorial2::field::FieldBase<>,
            TExtraOpts...,
            typename TOpt::field::S6_2,
            comms::option::def::SequenceSerLengthFieldPrefix<typename S6_2Members<TOpt>::Length>
        >;
public:
    /// @brief Default constructor
    S6_2()
    {
        static const char Str[] = "hello";
        static const std::size_t StrSize = std::extent<decltype(Str)>::value;
        Base::value() = typename Base::ValueType(&Str[0], StrSize - 1);
    }
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::S6_2Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2


