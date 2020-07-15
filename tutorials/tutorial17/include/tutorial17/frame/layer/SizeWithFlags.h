#pragma once

#include "comms/protocol/MsgSizeLayer.h"
#include "comms/options.h"

namespace tutorial17
{

namespace frame
{

namespace layer
{

/// @brief Customizing the size layer
template<typename TField, typename TNextLayer, typename... TOptions>
class SizeWithFlags : public
    comms::protocol::MsgSizeLayer<
        TField,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<SizeWithFlags<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::MsgSizeLayer<
            TField,
            TNextLayer,
            TOptions...,
            comms::option::def::ExtendingClass<SizeWithFlags<TField, TNextLayer, TOptions...> >
        >;

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    

    // Given the combined bitfield field, retrieve remaining size
    static std::size_t getRemainingSizeFromField(const Field& field)
    {
        return static_cast<std::size_t>(field.field_size().value());
    }

    // Before forwarding read to the next layer update flags extra transport field in the interface
    template<typename TMsg> 
    static void beforeRead(const Field& field, TMsg* msg)
    {
        COMMS_ASSERT(msg != nullptr); // The message object is expected to be created
        msg->transportField_flags().setBitValue_B0(field.field_flags().getBitValue_F1());
    } 

    // Prepare field value to be written
    template <typename TMsg>
    static void prepareFieldForWrite(std::size_t size, const TMsg* msg, Field& field)
    {
        assert(msg != nullptr);
        field.field_size().value() = static_cast<typename Field::Field_size::ValueType>(size);
        field.field_flags().setBitValue_F1(msg->transportField_flags().getBitValue_B0());
    }
};

} // namespace layer

} // namespace frame

} // namespace tutorial17



