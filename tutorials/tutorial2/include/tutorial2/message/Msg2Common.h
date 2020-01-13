// Generated by commsdsl2comms v3.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg2 message and its fields.

#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <utility>
#include "tutorial2/field/E2_1Common.h"
#include "tutorial2/field/E2_2Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg2 message.
/// @see tutorial2::message::Msg2Fields
struct Msg2FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F1 field.
    struct F1Common : public tutorial2::field::E2_1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F2 field.
    struct F2Common : public tutorial2::field::E2_2Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
        
    };
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F3 field.
    struct F3Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::message::Msg2Fields::F3 field.
        enum class ValueType : std::int8_t
        {
            V1 = -100, ///< value @b V1
            V2 = 0, ///< value @b V2
            V3 = 10, ///< value @b V3
            
            // --- Extra values generated for convenience ---
            FirstValue = -100, ///< First defined value.
            LastValue = 10, ///< Last defined value.
            ValuesLimit = 11, ///< Upper limit for defined values.
            
        };
        
        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F3 field.
        static const char* name()
        {
            return "F3";
        }
        
        /// @brief Retrieve name of the enum value
        static const char* valueName(ValueType val)
        {
            using NameInfo = std::pair<ValueType, const char*>;
            static const NameInfo Map[] = {
                std::make_pair(ValueType::V1, "V1"),
                std::make_pair(ValueType::V2, "V2"),
                std::make_pair(ValueType::V3, "V3")
            };
            
            auto iter = std::lower_bound(
                std::begin(Map), std::end(Map), val,
                [](const NameInfo& info, ValueType v) -> bool
                {
                    return info.first < v;
                });
            
            if ((iter == std::end(Map)) || (iter->first != val)) {
                return nullptr;
            }
            
            return iter->second;
        }
        
    };
    
    /// @brief Values enumerator for
    ///     @ref tutorial2::message::Msg2Fields::F3 field.
    using F3Val = F3Common::ValueType;
    
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg2Fields::F4 field.
    struct F4Common
    {
        /// @brief Values enumerator for
        ///     @ref tutorial2::message::Msg2Fields::F4 field.
        enum class ValueType : std::int16_t
        {
            V1 = -200, ///< value @b V1
            V2 = 0, ///< value @b V2
            V3 = 255, ///< value @b V3
            V4 = 767, ///< value @b V4
            
            // --- Extra values generated for convenience ---
            FirstValue = -200, ///< First defined value.
            LastValue = 767, ///< Last defined value.
            ValuesLimit = 768, ///< Upper limit for defined values.
            
        };
        
        /// @brief Name of the @ref tutorial2::message::Msg2Fields::F4 field.
        static const char* name()
        {
            return "F4";
        }
        
        /// @brief Retrieve name of the enum value
        static const char* valueName(ValueType val)
        {
            using NameInfo = std::pair<ValueType, const char*>;
            static const NameInfo Map[] = {
                std::make_pair(ValueType::V1, "V1"),
                std::make_pair(ValueType::V2, "V2"),
                std::make_pair(ValueType::V3, "V3"),
                std::make_pair(ValueType::V4, "V4")
            };
            
            auto iter = std::lower_bound(
                std::begin(Map), std::end(Map), val,
                [](const NameInfo& info, ValueType v) -> bool
                {
                    return info.first < v;
                });
            
            if ((iter == std::end(Map)) || (iter->first != val)) {
                return nullptr;
            }
            
            return iter->second;
        }
        
    };
    
    /// @brief Values enumerator for
    ///     @ref tutorial2::message::Msg2Fields::F4 field.
    using F4Val = F4Common::ValueType;
    
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg2 message.
/// @see tutorial2::message::Msg2
struct Msg2Common
{
    /// @brief Name of the @ref tutorial2::message::Msg2 message.
    static const char* name()
    {
        return "Message 2";
    }
    
};

} // namespace message

} // namespace tutorial2


