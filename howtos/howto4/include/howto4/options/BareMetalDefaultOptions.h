// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains definition of protocol default options for bare-metal application
///    where usage of dynamic memory allocation is disabled.

#pragma once

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

#include "howto4/options/DefaultOptions.h"

namespace howto4
{

namespace options
{

/// @brief Default options for bare-metal application where usage of dynamic
///    memory allocation is diabled.
/// @tparam TBase Options to use as a basis.
template <typename TBase = howto4::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    /// @brief Extra options for fields.
    struct field : public TBase::field
    {
        /// @brief Extra options for all the member fields of
        ///     @ref howto4::field::TlvProp bitfield.
        struct TlvPropMembers : public TBase::field::TlvPropMembers
        {
            /// @brief Extra options for all the member fields of
            ///     @ref howto4::field::TlvPropMembers::Prop3 bundle.
            struct Prop3Members : public TBase::field::TlvPropMembers::Prop3Members
            {
                /// @brief Extra options for @ref
                ///     howto4::field::TlvPropMembers::Prop3Members::Val
                ///     field.
                using Val = 
                    std::tuple<
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                        typename TBase::field::TlvPropMembers::Prop3Members::Val
                    >;
            };
            
            /// @brief Extra options for all the member fields of
            ///     @ref howto4::field::TlvPropMembers::Any bundle.
            struct AnyMembers : public TBase::field::TlvPropMembers::AnyMembers
            {
                /// @brief Extra options for @ref
                ///     howto4::field::TlvPropMembers::AnyMembers::Val
                ///     field.
                using Val = 
                    std::tuple<
                        comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                        typename TBase::field::TlvPropMembers::AnyMembers::Val
                    >;
            };
            
        };
        
    }; // struct field
    
    /// @brief Extra options for messages.
    struct message : public TBase::message
    {
        /// @brief Extra options for fields of
        ///     @ref howto4::message::Msg message.
        struct MsgFields : public TBase::message::MsgFields
        {
            /// @brief Extra options for @ref
            ///     howto4::message::MsgFields::Props field.
            using Props = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                    typename TBase::message::MsgFields::Props
                >;
        }; // struct MsgFields
        
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for Layers of
        ///     @ref howto4::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto4::frame::FrameLayers::Data layer.
            using Data = std::tuple<
                comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                typename TBase::frame::FrameLayers::Data
            >;
            
            /// @brief Extra options for @ref
            ///     howto4::frame::FrameLayers::Id layer.
            using Id = std::tuple<
                comms::option::app::InPlaceAllocation,
                typename TBase::frame::FrameLayers::Id
            >;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Alias to @ref BareMetalDefaultOptionsT with default template parameter.
using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;

} // namespace options

} // namespace howto4


