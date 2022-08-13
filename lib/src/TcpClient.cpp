#include "TcpClient.h"

#include <iostream>
#include <sstream>

namespace cc_tutorial
{

TcpClient::TcpClient(boost_wrap::io& io)
  : m_io(io),
    m_session(Session::createClient(io))
{
    m_session->setTerminateCb(
        [this]()
        {
            m_io.stop();
        });
}

bool TcpClient::start(PortType port)
{
    SocketPtr socket(new Socket(m_io));
    boost::system::error_code ec;
    socket->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port), ec);
    if (ec) {
        std::cerr << "ERROR: Failed to connect with error: " << ec.message();
        return false;
    }

    m_session->setSocket(std::move(socket));
    return m_session->start();
}

} // namespace cc_tutorial
