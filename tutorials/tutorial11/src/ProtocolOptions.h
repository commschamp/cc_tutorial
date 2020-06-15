#pragma once

#include "tutorial11/options/DefaultOptions.h"

namespace cc_tutorial
{

template <typename TBase = tutorial11::options::DefaultOptions>
struct ProtocolOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            using Id = 
                std::tuple<
                    comms::option::app::ForceDispatchStaticBinSearch,
                    typename TBase::frame::FrameLayers::Id
                >;
            
        }; // struct FrameLayers
        
    }; // struct frame
};

using ProtocolOptions = ProtocolOptionsT<>;

} // namespace cc_tutorial