#pragma once

#include "comms/protocol/MsgIdLayer.h"
#include "comms/options.h"

namespace howto2
{

namespace frame
{

namespace layer
{

/// @brief Customizing the Id layer
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class IdWithSize : public
    comms::protocol::MsgIdLayer<
        TField,
        TMessage,
        TAllMessages,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<IdWithSize<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
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
            comms::option::def::ExtendingClass<IdWithSize<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
        >;

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    
    using MsgIdType = typename Base::MsgIdType;
    using MsgIdParamType = typename Base::MsgIdParamType;

    // Replacement of comms::MsgIdLayer::doRead
    template <typename TMsg, typename TIter, typename TNextLayerReader, typename... TExtraValues>
    comms::ErrorStatus doRead(
        Field& field, 
        TMsg& msg, 
        TIter& iter, 
        std::size_t size, 
        TNextLayerReader&& nextLayerReader, 
        TExtraValues... extraValues)
    {
        auto iterTmp = iter;
        Field fieldTmp;

        auto es = fieldTmp.read(iterTmp, size);
        if (es != comms::ErrorStatus::Success) {
            return 
                Base::doRead(
                    field, 
                    msg, 
                    iter, 
                    size, 
                    std::forward<TNextLayerReader>(nextLayerReader), 
                    extraValues...);
        }

        auto lenInField = static_cast<std::size_t>(fieldTmp.field_size().value());
        auto remLen = std::min(size, lenInField + fieldTmp.length());
        return 
            Base::doRead(
                field, 
                msg, 
                iter, 
                remLen, 
                std::forward<TNextLayerReader>(nextLayerReader), 
                extraValues...);
    }

    // Given the combined bitfield field, retrieve message ID value
    static MsgIdType getMsgIdFromField(const Field& field)
    {
        return field.field_msgId().value();
    }

    // Prepare field value to be written
    template <typename TMsg>
    void prepareFieldForWrite(MsgIdParamType id, const TMsg& msg, Field& field) const
    {
        field.field_msgId().value() = id;
        comms::cast_assign(field.field_size().value()) = Base::nextLayer().length(msg);
    }
};

} // namespace layer

} // namespace frame

} // namespace howto2



