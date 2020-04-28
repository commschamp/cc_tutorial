#pragma once

#include <map>

#include "Session.h"

namespace cc_tutorial
{

class TcpClient
{
public:
    using Socket = Session::Socket;
    using PortType = unsigned short;

    explicit TcpClient(boost_wrap::io& io);
    bool start(PortType port = 20000);

private:
    boost_wrap::io& m_io;
    SessionPtr m_session;
};


} // namespace cc_tutorial
