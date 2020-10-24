// Generated by commsdsl2comms v3.5.3

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto1::field::MsgId field.

#pragma once

#include <cstdint>
#include <type_traits>
#include "howto1/MsgId.h"

namespace howto1
{

namespace field
{

/// @brief Common types and functions for
///     @ref howto1::field::MsgId field.
struct MsgIdCommon
{
    /// @brief Values enumerator for
    ///     @ref howto1::field::MsgId field.
    using ValueType = howto1::MsgId;
    
    /// @brief Name of the @ref howto1::field::MsgId field.
    static const char* name()
    {
        return "MsgId";
    }
    
    /// @brief Retrieve name of the enum value
    static const char* valueName(howto1::MsgId val)
    {
        static const char* Map[] = {
            nullptr,
            "Message 1",
            "Message 2"
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        
        if (MapSize <= static_cast<std::size_t>(val)) {
            return nullptr;
        }
        
        return Map[static_cast<std::size_t>(val)];
    }
    
};

/// @brief Values enumerator for
///     @ref howto1::field::MsgId field.
using MsgIdVal = MsgIdCommon::ValueType;

} // namespace field

} // namespace howto1


