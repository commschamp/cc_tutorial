#pragma once

#include <limits>

#include "comms/protocol/TransportValueLayer.h"
#include "comms/options.h"

namespace howto5
{

namespace frame
{

namespace layer
{

/// @brief Customizing the TransportValueLayer
template<typename TField, typename TNextLayer, typename... TOptions>
class VersionWithFlags : public
    comms::protocol::TransportValueLayer<
        TField,
        std::numeric_limits<std::size_t>::max(), // Not used, the value doesn't matter
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<VersionWithFlags<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::TransportValueLayer<
            TField,
            std::numeric_limits<std::size_t>::max(),
            TNextLayer,
            TOptions...,
            comms::option::def::ExtendingClass<VersionWithFlags<TField, TNextLayer, TOptions...> >
        >;

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    

protected:    
    // Re-assign the values from the field to message object
    template <typename TMsg>
    static void reassignFieldValue(TMsg& msg, const Field& field)
    {
        msg.transportField_version().value() = field.field_version().value();
        msg.transportField_flags().value() = field.field_flags().value();
    }  

    // Prepare field value to be written
    template <typename TMsg>
    static void prepareFieldForWrite(const TMsg& msg, Field& field)
    {
        field.field_version().value() = msg.transportField_version().value();
        field.field_flags().value() = msg.transportField_flags().value();
    }      
};

} // namespace layer

} // namespace frame

} // namespace howto5



