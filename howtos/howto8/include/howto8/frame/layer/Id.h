#pragma once

#include <limits>

#include "comms/protocol/MsgIdLayer.h"
#include "comms/options.h"

namespace howto8
{

namespace frame
{

namespace layer
{

/// @brief Customizing the MsgIdLayer
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class Id : public
    comms::protocol::MsgIdLayer<
        TField,
        TMessage,
        TAllMessages,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<Id<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
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
            comms::option::def::ExtendingClass<Id<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
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

    // Before forwarding read to the next layer let the flags layer know
    // whether its field is present
    template<typename TMsg> 
    void beforeRead(const Field& field, TMsg& msg)
    {
        static_cast<void>(msg);
        bool hasFlags = field.field_ctrl().getBitValue_HasFlags();
        Base::nextLayer().setFieldPreset(hasFlags);
    } 

    // Prepare field value to be written
    template <typename TMsg>
    void prepareFieldForWrite(MsgIdParamType id, const TMsg& msg, Field& field) const
    {
        bool hasFlags = Base::nextLayer().isFieldPresent(msg);
        field.field_msgId().value() = id;
        field.field_ctrl().setBitValue_HasFlags(hasFlags);
    }
};
   
} // namespace layer

} // namespace frame

} // namespace howto8



