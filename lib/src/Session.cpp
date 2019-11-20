#include "Session.h"

#include <iostream>
#include <cassert>

namespace cc_tutorial
{

bool Session::start()
{
    assert(m_socket.is_open());

    if (!startImpl()) {
        return false;
    }

    doRead();
    return true;
}

bool Session::startImpl()
{
    return true;
}

void Session::sendOutput(const std::uint8_t* buf, std::size_t bufLen)
{
    if (!m_socket.is_open()) {
        return;
    }

    std::size_t consumed = 0U;
    while (consumed < bufLen) {
        boost::system::error_code ec;
        consumed += boost::asio::write(m_socket, boost::asio::buffer(buf, bufLen), ec);
        if (ec) {
            std::cerr << "ERROR: Failed to write: " << ec.message() << std::endl;
            terminateSession();
            return;
        }
    }
}

void Session::terminateSession()
{
    assert(m_terminateCb);
    m_terminateCb();
}

void Session::doRead()
{
    assert(m_socket.is_open());
    m_socket.async_read_some(
        boost::asio::buffer(m_inBuf),
        [this](const boost::system::error_code& ec, std::size_t bytesCount)
        {
            if (ec == boost::asio::error::operation_aborted) {
                return;
            }

            if (ec) {
                std::cerr << "ERROR: Failed to read: " << ec.message() << std::endl;
                terminateSession();
                return;
            }

            auto* buf = &m_inBuf[0];
            auto bufLen = bytesCount;
            bool useVector = !m_inData.empty();
            if (useVector) {
                m_inData.insert(m_inData.end(), buf, buf + bufLen);
                buf = &m_inData[0];
                bufLen = m_inData.size();
            }

            auto consumed = processInputImpl(buf, bufLen);
            if (useVector) {
                m_inData.erase(m_inData.begin(), m_inData.begin() + consumed);
            }
            else {
                auto begIter = buf + consumed;
                auto endIter = begIter + (bufLen - consumed);
                m_inData.assign(begIter, endIter);
            }

            doRead();
        });
}

} // namespace cc_tutorial
