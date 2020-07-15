#pragma once

#include "comms/protocol/MsgIdLayer.h"
#include "comms/options.h"

namespace tutorial17
{

namespace frame
{

namespace layer
{

/// @brief Customizing the Id layer
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class IdWithFlags : public
    comms::protocol::MsgIdLayer<
        TField,
        TMessage,
        TAllMessages,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<IdWithFlags<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::MsgIdLayer<
            TField,
            TMessage,
            TAllMessages,
            TNextLayer,
            TOptions...,
            comms::option::def::ExtendingClass<IdWithFlags<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
        >;

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    
    using MsgIdType = typename Base::MsgIdType;
    using MsgIdParamType = typename Base::MsgIdParamType;

    // Given the combined bitfield field, retrieve message ID value
    static MsgIdType getMsgIdFromField(const Field& field)
    {
        return field.field_msgId().value();
    }

    // Before forwarding read to the next layer update flags extra transport field in the interface
    template<typename TMsg> 
    static void beforeRead(const Field& field, TMsg& msg)
    {
        msg.transportField_flags().setBitValue_B1(field.field_flags().getBitValue_F1());
    } 

    // Prepare field value to be written
    template <typename TMsg>
    static void prepareFieldForWrite(MsgIdParamType id, const TMsg& msg, Field& field)
    {
        field.field_msgId().value() = id;
        field.field_flags().setBitValue_F1(msg.transportField_flags().getBitValue_B1());
    }
};

} // namespace layer

} // namespace frame

} // namespace tutorial17



