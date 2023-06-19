// Generated by commsdsl2comms v6.2.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial22::field::TlvProp field.

#pragma once

#include <cstdint>
#include "tutorial22/field/LengthCommon.h"

namespace tutorial22
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial22::field::TlvProp field.
struct TlvPropMembersCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial22::field::TlvPropMembers::Prop1 field.
    struct Prop1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::Prop1Members::Key field.
        struct KeyCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial22::field::TlvPropMembers::Prop1Members::Key field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Prop1Members::Key field.
            static const char* name()
            {
                return "Key";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };

        /// @brief Common definitions of the member fields of
        ///     @ref tutorial22::field::TlvPropMembers::Prop1Members::Length field.
        using LengthMembersCommon = tutorial22::field::LengthMembersCommon;

        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::Prop1Members::Length field.
        using LengthCommon = tutorial22::field::LengthCommon;

        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::Prop1Members::Val field.
        struct ValCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial22::field::TlvPropMembers::Prop1Members::Val field.
            using ValueType = std::uint32_t;

            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Prop1Members::Val field.
            static const char* name()
            {
                return "Val";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial22::field::TlvPropMembers::Prop1 field.
    struct Prop1Common
    {
        /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Prop1 field.
        static const char* name()
        {
            return "Prop1";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial22::field::TlvPropMembers::Prop2 field.
    struct Prop2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::Prop2Members::Key field.
        struct KeyCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial22::field::TlvPropMembers::Prop2Members::Key field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Prop2Members::Key field.
            static const char* name()
            {
                return "Key";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };

        /// @brief Common definitions of the member fields of
        ///     @ref tutorial22::field::TlvPropMembers::Prop2Members::Length field.
        using LengthMembersCommon = tutorial22::field::LengthMembersCommon;

        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::Prop2Members::Length field.
        using LengthCommon = tutorial22::field::LengthCommon;

        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::Prop2Members::Val field.
        struct ValCommon
        {
            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Prop2Members::Val field.
            static const char* name()
            {
                return "Val";
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial22::field::TlvPropMembers::Prop2 field.
    struct Prop2Common
    {
        /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Prop2 field.
        static const char* name()
        {
            return "Prop2";
        }
    };

    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial22::field::TlvPropMembers::Any field.
    struct AnyMembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::AnyMembers::Key field.
        struct KeyCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial22::field::TlvPropMembers::AnyMembers::Key field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::AnyMembers::Key field.
            static const char* name()
            {
                return "Key";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };

        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::AnyMembers::Length field.
        struct LengthCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial22::field::TlvPropMembers::AnyMembers::Length field.
            using ValueType = std::uint8_t;

            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::AnyMembers::Length field.
            static const char* name()
            {
                return "Length";
            }

            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return false;
            }
        };

        /// @brief Common types and functions for
        ///     @ref tutorial22::field::TlvPropMembers::AnyMembers::Val field.
        struct ValCommon
        {
            /// @brief Name of the @ref tutorial22::field::TlvPropMembers::AnyMembers::Val field.
            static const char* name()
            {
                return "Val";
            }
        };
    };

    /// @brief Common types and functions for
    ///     @ref tutorial22::field::TlvPropMembers::Any field.
    struct AnyCommon
    {
        /// @brief Name of the @ref tutorial22::field::TlvPropMembers::Any field.
        static const char* name()
        {
            return "Any";
        }
    };
};

/// @brief Common types and functions for
///     @ref tutorial22::field::TlvProp field.
struct TlvPropCommon
{
    /// @brief Name of the @ref tutorial22::field::TlvProp field.
    static const char* name()
    {
        return "TlvProp";
    }
};

} // namespace field

} // namespace tutorial22
