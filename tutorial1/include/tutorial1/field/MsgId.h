/// @file
/// @brief Contains definition of <b>"MsgId"</b> field.

#pragma once

#include <cstdint>
#include <type_traits>
#include "comms/field/EnumValue.h"
#include "comms/options.h"
#include "tutorial1/MsgId.h"
#include "tutorial1/field/FieldBase.h"
#include "tutorial1/options/DefaultOptions.h"

namespace tutorial1
{

namespace field
{

/// @brief Common functions for
///     @ref tutorial1::field::MsgId field.
struct MsgIdCommon
{
    /// @brief Retrieve name of the enum value
    static const char* valueName(tutorial1::MsgId val)
    {
        static const char* Map[] = {
            nullptr,
            "M1",
            "M2"
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        
        if (MapSize <= static_cast<std::size_t>(val)) {
            return nullptr;
        }
        
        return Map[static_cast<std::size_t>(val)];
    }
    
};

/// @brief Definition of <b>"MsgId"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial1::options::DefaultOptions, typename... TExtraOpts>
struct MsgId : public
    comms::field::EnumValue<
        tutorial1::field::FieldBase<>,
        tutorial1::MsgId,
        TExtraOpts...,
        comms::option::def::ValidNumValueRange<1, 2>
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return "MsgId";
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(tutorial1::MsgId val)
    {
        return tutorial1::field::MsgIdCommon::valueName(val);
    }
    
};

} // namespace field

} // namespace tutorial1


