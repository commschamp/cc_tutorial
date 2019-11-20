#pragma once

#include <map>

#include <boost/asio.hpp>

#include "Session.h"

namespace cc_tutorial
{

class TcpServer
{
public:
    using Acceptor = boost::asio::ip::tcp::acceptor;
    using Socket = boost::asio::ip::tcp::socket;
    using PortType = unsigned short;

    explicit TcpServer(boost::asio::io_service& io);
    bool start(PortType port = 20000);

private:

    using SessionsMap = std::map<std::string, SessionPtr>;

    void doAccept();

    Acceptor m_acceptor;
    Socket m_socket;
    SessionsMap m_sessions;
};


} // namespace cc_tutorial
