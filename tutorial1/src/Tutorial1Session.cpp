#include "Tutorial1Session.h"

namespace cc_tutorial
{

std::size_t Tutorial1Session::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    static_cast<void>(buf);
    static_cast<void>(bufLen);
    return 0U;
}

SessionPtr Session::createServer(boost::asio::io_service& io)
{
    return SessionPtr(new Tutorial1Session(io));
}

} // namespace cc_tutorial
