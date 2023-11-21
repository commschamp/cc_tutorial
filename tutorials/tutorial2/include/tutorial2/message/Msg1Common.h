// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg1 message and its fields.

#pragma once

#include <cstdint>
#include "tutorial2/field/I1Common.h"

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg1 message.
/// @see tutorial2::message::Msg1Fields
struct Msg1FieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg1Fields::F1 field.
    struct F1Common : public tutorial2::field::I1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg1Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg1Fields::F2 field.
    struct F2Common
    {
        /// @brief Re-definition of the value type used by
        ///     tutorial2::message::Msg1Fields::F2 field.
        using ValueType = std::int16_t;

        /// @brief Name of the @ref tutorial2::message::Msg1Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }

        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return false;
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg1 message.
struct Msg1Common
{
    /// @brief Name of the @ref tutorial2::message::Msg1 message.
    static const char* name()
    {
        return "Message 1";
    }
};

} // namespace message

} // namespace tutorial2
