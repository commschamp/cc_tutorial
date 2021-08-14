// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial4::field::KeyValueProp field.

#pragma once

#include <cstdint>

namespace tutorial4
{

namespace field
{

/// @brief Scope for all the common definitions of the member fields of
///     @ref tutorial4::field::KeyValueProp bundle.
struct KeyValuePropMembersCommon
{
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial4::field::KeyValuePropMembers::Prop1 field.
    struct Prop1MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop1Members::Key field.
        struct KeyCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial4::field::KeyValuePropMembers::Prop1Members::Key field.
            using ValueType = std::uint8_t;
        
            /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop1Members::Key field.
            static const char* name()
            {
                return "Key";
            }
            
        };
        
        /// @brief Common types and functions for
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop1Members::Val field.
        struct ValCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial4::field::KeyValuePropMembers::Prop1Members::Val field.
            using ValueType = std::uint16_t;
        
            /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop1Members::Val field.
            static const char* name()
            {
                return "Val";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial4::field::KeyValuePropMembers::Prop1 field.
    struct Prop1Common
    {
        /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop1 field.
        static const char* name()
        {
            return "Prop1";
        }
        
    };
    
    
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial4::field::KeyValuePropMembers::Prop2 field.
    struct Prop2MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop2Members::Key field.
        struct KeyCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial4::field::KeyValuePropMembers::Prop2Members::Key field.
            using ValueType = std::uint8_t;
        
            /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop2Members::Key field.
            static const char* name()
            {
                return "Key";
            }
            
        };
        
        /// @brief Common types and functions for
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop2Members::Val field.
        struct ValCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial4::field::KeyValuePropMembers::Prop2Members::Val field.
            using ValueType = float;
        
            /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop2Members::Val field.
            static const char* name()
            {
                return "Val";
            }
            
        };
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial4::field::KeyValuePropMembers::Prop2 field.
    struct Prop2Common
    {
        /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop2 field.
        static const char* name()
        {
            return "Prop2";
        }
        
    };
    
    
    /// @brief Scope for all the common definitions of the member fields of
    ///     @ref tutorial4::field::KeyValuePropMembers::Prop3 field.
    struct Prop3MembersCommon
    {
        /// @brief Common types and functions for
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop3Members::Key field.
        struct KeyCommon
        {
            /// @brief Re-definition of the value type used by
            ///     tutorial4::field::KeyValuePropMembers::Prop3Members::Key field.
            using ValueType = std::uint8_t;
        
            /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop3Members::Key field.
            static const char* name()
            {
                return "Key";
            }
            
        };
        
        /// @brief Scope for all the common definitions of the member fields of
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop3Members::Val field.
        struct ValMembersCommon
        {
            /// @brief Common types and functions for
            ///     @ref tutorial4::field::KeyValuePropMembers::Prop3Members::ValMembers::Length field.
            struct LengthCommon
            {
                /// @brief Re-definition of the value type used by
                ///     tutorial4::field::KeyValuePropMembers::Prop3Members::ValMembers::Length field.
                using ValueType = std::uint8_t;
            
                /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop3Members::ValMembers::Length field.
                static const char* name()
                {
                    return "Length";
                }
                
            };
            
        };
        
        /// @brief Scope for all the common definitions of the
        ///     @ref tutorial4::field::KeyValuePropMembers::Prop3Members::Val field.
        struct ValCommon
        {
            /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop3Members::Val field.
            static const char* name()
            {
                return "Val";
            }
            
        };
        
        
    };
    
    /// @brief Scope for all the common definitions of the
    ///     @ref tutorial4::field::KeyValuePropMembers::Prop3 field.
    struct Prop3Common
    {
        /// @brief Name of the @ref tutorial4::field::KeyValuePropMembers::Prop3 field.
        static const char* name()
        {
            return "Prop3";
        }
        
    };
    
    
};

/// @brief Scope for all the common definitions of the
///     @ref tutorial4::field::KeyValueProp field.
struct KeyValuePropCommon
{
    /// @brief Name of the @ref tutorial4::field::KeyValueProp field.
    static const char* name()
    {
        return "KeyValueProp";
    }
    
};


} // namespace field

} // namespace tutorial4


