#pragma once

#include "tutorial12/options/BareMetalDefaultOptions.h"

namespace cc_tutorial
{

// Expects to wrap a variant of tutorial12::options::BareMetalDefaultOptionsT
template <typename TBase = tutorial12::options::BareMetalDefaultOptions>
struct BareMetalProtocolOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct Msg1Fields : public TBase::message::Msg1Fields
        {
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<8>,
                    typename TBase::message::Msg1Fields::F1
                >;
        }; // struct Msg1Fields
    }; // struct frame
};

using BareMetalProtocolOptions = BareMetalProtocolOptionsT<>;

} // namespace cc_tutorial