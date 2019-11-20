#pragma once

#include <memory>
#include <vector>
#include <array>

#include <boost/asio.hpp>

namespace cc_tutorial
{

class Session
{
public:
    using Ptr = std::unique_ptr<Session>;
    using Socket = boost::asio::ip::tcp::socket;

    virtual ~Session() = default;

    void setSocket(Socket&& socket)
    {
        m_socket = std::move(socket);
    }

    // Needs to be implemented inside every tutorial
    static Ptr createServer(boost::asio::io_service& io);
    static Ptr createClient(boost::asio::io_service& io);

    bool start();

    using TerminateCb = std::function<void ()>;
    template <typename TFunc>
    void setTerminateCb(TFunc&& func)
    {
        m_terminateCb = std::forward<TFunc>(func);
    }

    boost::asio::io_service& getIoService()
    {
        return m_socket.get_io_service();
    }

protected:
    explicit Session(boost::asio::io_service& io) :
        m_socket(io)
    {
    }

    virtual bool startImpl();
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) = 0;

    void sendOutput(const std::uint8_t* buf, std::size_t bufLen);
    void terminateSession();

private:
    void doRead();

    Socket m_socket;
    std::array<std::uint8_t, 1024> m_inBuf;
    std::vector<std::uint8_t> m_inData;
    TerminateCb m_terminateCb;
};

using SessionPtr = std::unique_ptr<Session>;

} // namespace cc_tutorial
