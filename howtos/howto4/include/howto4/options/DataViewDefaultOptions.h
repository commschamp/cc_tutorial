// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of protocol data view default options.

#pragma once

#include "howto4/options/DefaultOptions.h"

namespace howto4
{

namespace options
{

/// @brief Default data view options of the protocol.
template <typename TBase = howto4::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    /// @brief Extra options for fields.
    struct field : public TBase::field
    {
        struct TlvPropMembers : public TBase::field::TlvPropMembers
        {
            struct Prop3Members : public TBase::field::TlvPropMembers::Prop3Members
            {
                /// @brief Extra options for @ref
                ///     howto4::field::TlvPropMembers::Prop3Members::Val
                ///     field.
                using Val =
                    std::tuple<
                        comms::option::app::OrigDataView,
                        typename TBase::field::TlvPropMembers::Prop3Members::Val
                    >;
                
            }; // struct Prop3Members
            
            struct AnyMembers : public TBase::field::TlvPropMembers::AnyMembers
            {
                /// @brief Extra options for @ref
                ///     howto4::field::TlvPropMembers::AnyMembers::Val
                ///     field.
                using Val =
                    std::tuple<
                        comms::option::app::OrigDataView,
                        typename TBase::field::TlvPropMembers::AnyMembers::Val
                    >;
                
            }; // struct AnyMembers
            
        }; // struct TlvPropMembers
        
    }; // struct field
    
    /// @brief Extra options for frames.
    struct frame : public TBase::frame
    {
        /// @brief Extra options for layers of
        ///     @ref howto4::frame::Frame frame.
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            /// @brief Extra options for @ref
            ///     howto4::frame::FrameLayers::Data layer.
            using Data =
                std::tuple<
                    comms::option::app::OrigDataView,
                    typename TBase::frame::FrameLayers::Data
                >;
            
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

/// @brief Alias to @ref DataViewDefaultOptionsT with default template parameter.
using DataViewDefaultOptions = DataViewDefaultOptionsT<>;

} // namespace options

} // namespace howto4
