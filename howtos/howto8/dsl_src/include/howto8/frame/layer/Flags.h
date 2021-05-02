#pragma once

#include <limits>

#include "comms/protocol/TransportValueLayer.h"
#include "comms/options.h"

namespace howto8
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
        0, // Index of the "flags" extra transport fields in the interface
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<Flags<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = 
        comms::protocol::TransportValueLayer<
            TField,
            0,
            TNextLayer,
            TOptions...,
            comms::option::def::ExtendingClass<Flags<TField, TNextLayer, TOptions...> >
        >;

public:
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 

    // Extra public functions
    void setFieldPreset(bool value)
    {
        m_hasFlagsOnRead = value;    
    }

    template <typename TMsg>
    static bool isFieldPresent(const TMsg& msg)
    {
        return msg.transportField_flags().value() != 0U;
    }

    // Overriding default read field functionality
    template <typename TMsg, typename TIter>
    comms::ErrorStatus readField(const TMsg* msgPtr, Field& field, TIter& iter, std::size_t len)
    {
        auto mode = comms::field::OptionalMode::Missing;
        if (m_hasFlagsOnRead) {
            mode = comms::field::OptionalMode::Exists;
        }

        field.setMode(mode);
        return Base::readField(msgPtr, field, iter, len);
    }

    // Reassign the field value
    template <typename TMsg>
    static void reassignFieldValue(TMsg& msg, const Field& field)
    {
        msg.transportField_flags().value() = field.field().value();
    }    

    // Overriding default field praparation functionality
    template <typename TMsg>
    static void prepareFieldForWrite(const TMsg& msg, Field& field)
    {
        field.field().value() = msg.transportField_flags().value();
        auto mode = comms::field::OptionalMode::Missing;
        if (isFieldPresent(msg)) {
            mode = comms::field::OptionalMode::Exists;
        }
        field.setMode(mode);
    } 

    template <typename TMsg>
    static std::size_t doFieldLength(const TMsg& msg)
    {
        if (isFieldPresent(msg)) {
            return Field::maxLength(); // returns 1
        }

        return Field::minLength(); // returns 0
    }    
    
private:
    bool m_hasFlagsOnRead = false;    
};
   
} // namespace layer

} // namespace frame

} // namespace howto8



