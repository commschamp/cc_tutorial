// Generated by commsdsl2comms v6.2.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial12::message::Msg3 message and its fields.

#pragma once

#include <cstdint>

namespace tutorial12
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial12::message::Msg3 message.
/// @see tutorial12::message::Msg3Fields
struct Msg3FieldsCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial12::message::Msg3Fields::F1 field.
    struct F1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial12::message::Msg3Fields::F1Members::Element field.
        struct ElementCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial12::message::Msg3Fields::F1Members::Element field.
            using ValueType = std::uint32_t;

            /// @brief Name of the @ref tutorial12::message::Msg3Fields::F1Members::Element field.
            static const char* name()
            {
                return "Element";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial12::message::Msg3Fields::F1 field.
    struct F1Common
    {
        /// @brief Name of the @ref tutorial12::message::Msg3Fields::F1 field.
        static const char* name()
        {
            return "F1";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial12::message::Msg3Fields::F2 field.
    struct F2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial12::message::Msg3Fields::F2Members::Element field.
        struct ElementCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial12::message::Msg3Fields::F2Members::Element field.
            using ValueType = std::uint16_t;

            /// @brief Name of the @ref tutorial12::message::Msg3Fields::F2Members::Element field.
            static const char* name()
            {
                return "Element";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial12::message::Msg3Fields::F2 field.
    struct F2Common
    {
        /// @brief Name of the @ref tutorial12::message::Msg3Fields::F2 field.
        static const char* name()
        {
            return "F2";
        }
    };
};

/// @brief Common types and functions of 
///     @ref tutorial12::message::Msg3 message.
struct Msg3Common
{
    /// @brief Name of the @ref tutorial12::message::Msg3 message.
    static const char* name()
    {
        return "Message 3";
    }
};

} // namespace message

} // namespace tutorial12
