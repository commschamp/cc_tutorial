#pragma once

#include <limits>

#include "comms/protocol/SyncPrefixLayer.h"
#include "comms/options.h"

namespace howto7
{

namespace frame
{

namespace layer
{

/// @brief Customizing the SyncPrefixLayer
template<typename TField, typename TNextLayer, typename... TOptions>
class AlternatingSync : public
    comms::protocol::SyncPrefixLayer<
        TField,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<AlternatingSync<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::SyncPrefixLayer<
            TField,
            TNextLayer,
            TOptions...,
            comms::option::def::ExtendingClass<AlternatingSync<TField, TNextLayer, TOptions...> >
        >;

public:
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 

    // Customizing input field value verification logic
    bool verifyFieldValue(const Field& field)
    {
        bool valid = (field.value() == getPrefix(m_inputCount));
        if (valid) {
            ++m_inputCount;
        }
        return valid;
    } 

    // Customizing output field preparation logic
    void prepareFieldForWrite(Field& field) const
    {
        field.value() = getPrefix(m_outputCount);
        ++m_outputCount;
    }

private:
    static typename TField::ValueType getPrefix(unsigned count)
    {
        static const typename TField::ValueType Map[] = {
            0xabcd,
            0xdead
        };
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;

        auto idx = (count % MapSize);
        return Map[idx];
    }

    unsigned m_inputCount = 0;
    mutable unsigned m_outputCount = 0;
};
   
} // namespace layer

} // namespace frame

} // namespace howto7



