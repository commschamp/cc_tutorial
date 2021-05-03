#pragma once

#include <limits>

#include "comms/protocol/ChecksumLayer.h"
#include "comms/options.h"
#include "comms/protocol/checksum/BasicSum.h"
#include "comms/protocol/checksum/Crc.h"

#include "howto6/field/ChecksumTypeCommon.h"

namespace howto6
{

namespace frame
{

namespace layer
{

/// @brief Customizing the ChecksumLayer
template<typename TField, typename TNextLayer, typename... TOptions>
class Checksum : public
    comms::protocol::ChecksumLayer<
        TField,
        comms::protocol::checksum::Crc_32, // Not really used, but the parameter needs to be populated
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<Checksum<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::ChecksumLayer<
            TField,
            comms::protocol::checksum::Crc_32,
            TNextLayer,
            TOptions...,
            comms::option::def::ExtendingClass<Checksum<TField, TNextLayer, TOptions...> >
        >;

public:
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 
 
    // Override default way of calculating checksum
    template <typename TMsg, typename TIter>
    static typename Field::ValueType calculateChecksum(const TMsg* msgPtr, TIter& iter, std::size_t len, bool& checksumValid)
    {
        if (msgPtr == nullptr) {
            checksumValid = false;
            return static_cast<typename Field::ValueType>(0);
        }
    
        checksumValid = true;
        auto checksumType = msgPtr->transportField_checksumType().value();
        if (checksumType == howto6::field::ChecksumTypeCommon::ValueType::Sum8) {
            using Calc = comms::protocol::checksum::BasicSum<std::uint8_t>;
            return Calc()(iter, len);
        }
    
        if (checksumType == ChecksumType::Crc16) {
            using Calc = comms::protocol::checksum::Crc_16;
            return Calc()(iter, len);
        }        
    
        if (checksumType == ChecksumType::Crc32) {
            using Calc = comms::protocol::checksum::Crc_32;
            return Calc()(iter, len);
        }        
    
        checksumValid = false;
        return static_cast<typename Field::ValueType>(0);
    }    
 
    // Due to the fact that the used checksums have different lengths, the
    // functionality of reading a field's value also needs to be customized.
    template <typename TMsg, typename TIter>
    static comms::ErrorStatus doReadField(const TMsg* msgPtr, Field& field, TIter& iter, std::size_t len)
    {
        if (msgPtr == nullptr) {
            return comms::ErrorStatus::ProtocolError;
        }
    
        auto checksumType = msgPtr->transportField_checksumType().value();
        if (checksumType == ChecksumType::Sum8) {
            return readFieldInternal<std::uint8_t>(field, iter, len);
        }
 
        if (checksumType == ChecksumType::Crc16) {
            return readFieldInternal<std::uint16_t>(field, iter, len);
        }
 
        if (checksumType == ChecksumType::Crc32) {
            return readFieldInternal<std::uint32_t>(field, iter, len);
        }
 
        return comms::ErrorStatus::ProtocolError;
    }
 
    // Due to the fact that the used checksums have different lengths, the
    // functionality of reading a field's value also needs to be customized.
    template <typename TMsg, typename TIter>
    static comms::ErrorStatus doWriteField(const TMsg* msgPtr, const Field& field, TIter& iter, std::size_t len)
    {
        if (msgPtr == nullptr) {
            return comms::ErrorStatus::ProtocolError;
        }
    
        auto checksumType = msgPtr->transportField_checksumType().value();
        if (checksumType == ChecksumType::Sum8) {
            return writeFieldInternal<std::uint8_t>(field, iter, len);
        }
 
        if (checksumType == ChecksumType::Crc16) {
            return writeFieldInternal<std::uint16_t>(field, iter, len);
        }
 
        if (checksumType == ChecksumType::Crc32) {
            return writeFieldInternal<std::uint32_t>(field, iter, len);
        }
 
        return comms::ErrorStatus::ProtocolError;
    }
 
    // Due to the fact that the used checksums have different lengths, the
    // functionality of calculating the field's length needs to be overridden
    template <typename TMsg>
    static std::size_t doFieldLength(const TMsg& msg)
    {
        auto checksumType = msg.transportField_checksumType().value();
        if (checksumType == ChecksumType::Sum8) {
            return sizeof(std::uint8_t);
        }
 
        if (checksumType == ChecksumType::Crc16) {
            return sizeof(std::uint16_t);
        }
 
        if (checksumType == ChecksumType::Crc32) {
            return sizeof(std::uint32_t);
        }
 
        COMMS_ASSERT(!"Should not happen");
        return 0;
    }
 
private:
    using ChecksumType = howto6::field::ChecksumTypeCommon::ValueType;

    template <typename TTmpType, typename TIter>
    static comms::ErrorStatus readFieldInternal(Field& field, TIter& iter, std::size_t len)
    {
        using FieldTmp = comms::field::IntValue<typename Field::FieldBase, TTmpType>;
        FieldTmp fieldTmp;
        auto es = fieldTmp.read(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }
    
        field = comms::field_cast<Field>(fieldTmp);
        return es;
    }
 
    template <typename TTmpType, typename TIter>
    static comms::ErrorStatus writeFieldInternal(const Field& field, TIter& iter, std::size_t len)
    {
        using FieldTmp = comms::field::IntValue<typename Field::FieldBase, TTmpType>;
        auto fieldTmp = comms::field_cast<FieldTmp>(field); // Re-assign the field's value
        return fieldTmp.write(iter, len);
    }
};
   
} // namespace layer

} // namespace frame

} // namespace howto6



