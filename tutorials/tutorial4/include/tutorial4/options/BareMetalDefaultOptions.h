// Generated by commsdsl2comms v3.4.0

/// @file
/// @brief Contains definition of protocol default options for bare-metal application
///    where usage of dynamic memory allocation is disabled.

#pragma once

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

#include "tutorial4/options/DefaultOptions.h"

namespace tutorial4
{

namespace options
{

/// @brief Default options for bare-metal application where usage of dynamic
///    memory allocation is diabled.
/// @tparam TBase Options to use as a basis.
template <typename TBase = tutorial4::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    /// @brief Extra options for fields.
    struct field : public TBase::field
    {
        /// @brief Extra options for all the member fields of
        ///     @ref tutorial4::field::KeyValueProp bitfield.
        struct KeyValuePropMembers : public TBase::field::KeyValuePropMembers
        {
            /// @brief Extra options for all the member fields of
            ///     @ref tutorial4::field::KeyValuePropMembers::Prop3 bundle.
            struct Prop3Members : public TBase::field::KeyValuePropMembers::Prop3Members
            {
                /// @brief Extra options for @ref
                ///     tutorial4::field::KeyValuePropMembers::Prop3Members::Val
                ///     field.
                using Val = 
                    std::tuple<
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                        typename TBase::field::KeyValuePropMembers::Prop3Members::Val
                    >;
            };
            
        };
        
        /// @brief Extra options for all the member fields of
        ///     @ref tutorial4::field::TlvProp bitfield.
        struct TlvPropMembers : public TBase::field::TlvPropMembers
        {
            /// @brief Extra options for all the member fields of
            ///     @ref tutorial4::field::TlvPropMembers::Prop6 bundle.
            struct Prop6Members : public TBase::field::TlvPropMembers::Prop6Members
            {
                /// @brief Extra options for @ref
                ///     tutorial4::field::TlvPropMembers::Prop6Members::Val
                ///     field.
                using Val = 
                    std::tuple<
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                        typename TBase::field::TlvPropMembers::Prop6Members::Val
                    >;
            };
            
        };
        
    }; // struct field
    
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref tutorial4::message::Msg1 message.
        struct Msg1Fields : public TBase::message::Msg1Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial4::message::Msg1Fields::F1
            ///     field.
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                    typename TBase::message::Msg1Fields::F1
                >;
        }; // struct Msg1Fields
        
        
        /// @brief Extra options for fields of
        ///     @ref tutorial4::message::Msg2 message.
        struct Msg2Fields : public TBase::message::Msg2Fields
        {
            /// @brief Extra options for @ref
            ///     tutorial4::message::Msg2Fields::F1
            ///     field.
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                    typename TBase::message::Msg2Fields::F1
                >;
        }; // struct Msg2Fields
        
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for Layers of
        ///     @ref tutorial4::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial4::frame::FrameLayers::Data
            ///     layer.
            using Data = std::tuple<
                comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                typename TBase::frame::FrameLayers::Data
            >;
            
            /// @brief Extra options for @ref
            ///     tutorial4::frame::FrameLayers::ID layer.
            using ID = std::tuple<
                comms::option::app::InPlaceAllocation,
                typename TBase::frame::FrameLayers::ID
            >;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace tutorial4


