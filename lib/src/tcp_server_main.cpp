#include <iostream>
#include <csignal>
#include <stdexcept>

#include <cassert>

#include <boost/asio.hpp>

#include "TcpServer.h"

int main(int argc, const char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    try {
        boost::asio::io_service io;

        cc_tutorial::TcpServer server(io);

        if (!server.start()) {
            std::cerr << "Failed to start tcp server!" << std::endl;
            return -1;
        }

        boost::asio::signal_set termSignals(io, SIGTERM, SIGINT);
        termSignals.async_wait(
            [&io](const boost::system::error_code& ec, int sigNum)
            {
                static_cast<void>(ec);
                assert(!ec);
                std::cerr << "Terminating tcp server due to signal " << sigNum << std::endl;
                io.stop();
            });


        io.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected exception in tcp server: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
