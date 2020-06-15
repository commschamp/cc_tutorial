#include "ServerSession.h"

#include <iostream>
#include <cassert>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ServerSession::handle(Message& msg)
{
    static_cast<void>(msg);
    std::cerr << "ERROR: Received unexpected message" << std::endl;
}

std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    // Force static binary search dispatch
    using Dispatcher =
        comms::MsgDispatcher<comms::option::ForceDispatchStaticBinSearch>;    

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (handle() member function will be called)
    return comms::processAllWithDispatchViaDispatcher<Dispatcher>(buf, bufLen, m_frame, *this);
}

SessionPtr Session::createServer(boost_wrap::io& io)
{
    return SessionPtr(new ServerSession(io));
}

} // namespace cc_tutorial
