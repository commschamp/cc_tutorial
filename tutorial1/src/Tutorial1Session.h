#pragma once

#include "Session.h"

namespace cc_tutorial
{

class Tutorial1Session : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;
};

} // namespace cc_tutorial
