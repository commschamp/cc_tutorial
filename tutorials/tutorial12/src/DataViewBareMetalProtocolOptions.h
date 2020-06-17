#pragma once

#include "tutorial12/options/DataViewDefaultOptions.h"

namespace cc_tutorial
{

// Expects to wrap a variant of tutorial12::options::DataViewDefaultOptionsT
template <typename TBase = tutorial12::options::DataViewDefaultOptions>
struct DataViewBareMetalProtocolOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct Msg3Fields : public TBase::message::Msg3Fields
        {
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<16>,
                    typename TBase::message::Msg3Fields::F1
                >;

            using F2 = 
                std::tuple<
                    comms::option::app::SequenceFixedSizeUseFixedSizeStorage,
                    typename TBase::message::Msg3Fields::F2
                >;
        }; // struct Msg3Fields

        struct FrameLayers : public TBase::frame::FrameLayers
        {
            using Id = std::tuple<
                comms::option::app::InPlaceAllocation,
                typename TBase::frame::FrameLayers::Id
            >;
            
        }; // struct FrameLayers        

    }; // struct frame
};

using DataViewBareMetalProtocolOptions = DataViewBareMetalProtocolOptionsT<>;

} // namespace cc_tutorial