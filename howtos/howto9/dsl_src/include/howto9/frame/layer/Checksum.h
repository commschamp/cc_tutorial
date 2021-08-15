#pragma once

#include <limits>
#include <cstddef>
#include <iterator>

#include "comms/protocol/ChecksumPrefixLayer.h"
#include "comms/options.h"
#include "comms/protocol/checksum/BasicSum.h"
#include "comms/protocol/checksum/Crc.h"

#include "howto9/field/SyncFieldCommon.h"
#include "howto9/field/SizeFieldCommon.h"
#include "howto9/field/MsgIdCommon.h"

namespace howto9
{

namespace frame
{

namespace layer
{

/// @brief Customizing the ChecksumLayer
template<typename TField, typename TNextLayer, typename... TOptions>
class Checksum : public
    comms::protocol::ChecksumPrefixLayer<
        TField,
        comms::protocol::checksum::Crc_16, 
        TNextLayer,
        TOptions...,
        comms::option::def::ChecksumLayerVerifyBeforeRead,
        comms::option::def::ExtendingClass<Checksum<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::ChecksumPrefixLayer<
            TField,
            comms::protocol::checksum::Crc_16,
            TNextLayer,
            TOptions...,
            comms::option::def::ChecksumLayerVerifyBeforeRead,
            comms::option::def::ExtendingClass<Checksum<TField, TNextLayer, TOptions...> >
        >;

public:
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 
    using Calc = comms::protocol::checksum::Crc_16;
 
    // Override default way of calculating checksum
    template <typename TMsg, typename TIter>
    static typename Field::ValueType calculateChecksum(const TMsg* msgPtr, TIter& iter, std::size_t len, bool& checksumValid)
    {
        static_cast<void>(msgPtr); // Not used
        static_cast<void>(len); // Not used

        static const std::size_t CalcAreaSize = 
                sizeof(howto9::field::SyncFieldCommon::ValueType) + 
                sizeof(howto9::field::SizeFieldCommon::ValueType) + 
                sizeof(howto9::field::MsgIdCommon::ValueType);

        static const std::size_t HeaderSize = 
            CalcAreaSize + Field::maxLength();

        checksumValid = true;

        auto fromIter = iter;
        std::advance(iter, -static_cast<std::ptrdiff_t>(HeaderSize));

        return Calc()(fromIter, CalcAreaSize);
    }    
};
   
} // namespace layer

} // namespace frame

} // namespace howto9



