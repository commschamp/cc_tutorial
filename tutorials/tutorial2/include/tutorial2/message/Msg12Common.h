// Generated by commsdsl2comms v7.0.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::message::Msg12 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial2
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial2::message::Msg12 message.
/// @see tutorial2::message::Msg12Fields
struct Msg12FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial2::message::Msg12Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial2::message::Msg12Fields::F1Members::ActF1 field.
        struct ActF1Common
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial2::message::Msg12Fields::F1Members::ActF1 field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial2::message::Msg12Fields::F1Members::ActF1 field.
            static const char* name()
            {
                return "ActF1";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial2::message::Msg12Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial2::message::Msg12Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial2::message::Msg12 message.
struct Msg12Common
{
    /// @brief Name of the @ref tutorial2::message::Msg12 message.
    static const char* name()
    {
        return "Message 12";
    }
};

} // namespace message

} // namespace tutorial2
