#pragma once

#include <map>

#include <boost/asio.hpp>

#include "Session.h"

namespace cc_tutorial
{

class TcpClient
{
public:
    using Socket = Session::Socket;
    using PortType = unsigned short;

    explicit TcpClient(boost::asio::io_service& io);
    bool start(PortType port = 20000);

private:
    SessionPtr m_session;
};


} // namespace cc_tutorial
