#pragma once

#include <limits>
#include <cstddef>
#include <iterator>

#include "comms/protocol/TransportValueLayer.h"
#include "comms/options.h"

#include "howto10/Interface.h"

namespace howto10
{

namespace frame
{

namespace layer
{

/// @brief Customizing the TransportValueLayer
template<typename TField, typename TNextLayer, typename... TOptions>
class Flags : public
    comms::protocol::TransportValueLayer<
        TField,
        Interface<>::TransportFieldIdx_flags,
        TNextLayer,
        TOptions...,
        comms::option::def::ProtocolLayerSuppressReadUntilDataSplitForcing,
        comms::option::def::ExtendingClass<Flags<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::TransportValueLayer<
            TField,
            Interface<>::TransportFieldIdx_flags,
            TNextLayer,
            TOptions...,
            comms::option::def::ProtocolLayerSuppressReadUntilDataSplitForcing,
            comms::option::def::ExtendingClass<Flags<TField, TNextLayer, TOptions...> >
        >;

public:
    using Field = typename Base::Field;

    // Override the default functionaly of re-assigning the 
    // field value to the message object. Instead 
    // let the pseudo layer that follows the ID processing
    // to assign it when the message object is created.
    template <typename TMsg>
    bool reassignFieldValueToMsg(const Field& field, TMsg* msgPtr)
    {
        assert(msgPtr == nullptr); // The message object hasn't been created yet
        static_cast<void>(msgPtr);
        auto& idLayer = Base::nextLayer();
        auto& psedoFlagsLayer = idLayer.nextLayer();

        // Re-assign the field to the pseudo layer, which is going to 
        // assign it to the message object
        psedoFlagsLayer.pseudoField().value() = field.value();
        return true;
    }
};
   
} // namespace layer

} // namespace frame

} // namespace howto10


