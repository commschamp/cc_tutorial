#pragma once

#include <map>
#include <memory>

#include <boost/asio.hpp>

#include "Session.h"

namespace cc_tutorial
{

class TcpServer
{
public:
    using Acceptor = boost::asio::ip::tcp::acceptor;
    using Socket = boost::asio::ip::tcp::socket;
    using SocketPtr = std::unique_ptr<Socket>;
    using PortType = unsigned short;

    explicit TcpServer(boost_wrap::io& io);
    bool start(PortType port = 20000);

private:

    using SessionsMap = std::map<std::string, SessionPtr>;

    void doAccept();

    boost_wrap::io& m_io;
    Acceptor m_acceptor;
    SocketPtr m_socket;
    SessionsMap m_sessions;
};


} // namespace cc_tutorial
