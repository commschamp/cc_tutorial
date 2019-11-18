#include "TcpServer.h"

#include <iostream>
#include <sstream>

namespace cc_tutorial
{

TcpServer::TcpServer(boost::asio::io_service& io)
  : m_acceptor(io),
    m_socket(io)
{
}

bool TcpServer::start()
{
    boost::system::error_code ec;
    m_acceptor.open(boost::asio::ip::tcp::v4(), ec);
    if (ec) {
        std::cerr << "ERROR: Failed to open acceptor with error: " << ec.message();
        return false;
    }

    m_acceptor.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), m_port), ec);
    if (ec) {
        std::cerr << "ERROR: Failed to bind port " << m_port << " with error: " << ec.message() << std::endl;
        m_acceptor.close(ec);
        return false;
    }


    m_acceptor.listen(boost::asio::socket_base::max_connections, ec);
    if (ec) {
        std::cerr << "ERROR: Failed to put acceptor in the listen state with error: " << ec.message() << std::endl;
        m_acceptor.close(ec);
        return false;
    }

    doAccept();
    return true;
}

void TcpServer::doAccept()
{
    m_acceptor.async_accept(
        m_socket,
        [this](const boost::system::error_code& ec)
        {
            if (ec == boost::asio::error::operation_aborted) {
                return;
            }

            do {
                if (ec) {
                    std::cerr << "ERROR: Accept error: " << ec.message() << std::endl;
                    break;
                }

                std::stringstream stream;
                stream << m_socket.remote_endpoint();
                auto sessionId = stream.str();

                std::cout << "INFO: New connection from " << sessionId << std::endl;

                auto session = Session::createServer(m_acceptor.get_io_service());

                session->setTerminateCb(
                    [this, sessionId]()
                    {
                        auto iter = m_sessions.find(sessionId);
                        if (iter == m_sessions.end()) {
                            assert(!"Should not happen");
                            return;
                        }

                        m_sessions.erase(iter);
                    });

                session->setSocket(std::move(m_socket));
                if (!session->startServer()) {
                    std::cerr << "ERROR: Failed to start session for " << sessionId << std::endl;
                    break;
                }

                m_sessions.insert(std::make_pair(std::move(sessionId), std::move(session)));
            } while (false);

            doAccept();
        });
}

} // namespace cc_tutorial
