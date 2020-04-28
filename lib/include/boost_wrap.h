#pragma once

#include <boost/version.hpp>
#include <boost/asio.hpp>

namespace cc_tutorial
{

namespace boost_wrap
{

#define CC_TUTORIAL_BOOST_MAJOR (BOOST_VERSION / 100000)
#define CC_TUTORIAL_BOOST_MINOR ((BOOST_VERSION / 100) % 1000)

#if (CC_TUTORIAL_BOOST_MAJOR != 1)
#warning "Unexpected boost major version"
#endif

#if (CC_TUTORIAL_BOOST_MINOR < 66)

using io = boost::asio::io_service;

template <typename TFunc>
void post(io& i, TFunc&& func)
{
    i.post(std::forward<TFunc>(func));
}

#else // #if (CC_TUTORIAL_BOOST_MINOR < 66)

using io = boost::asio::io_context;

template <typename TFunc>
void post(io& i, TFunc&& func)
{
    boost::asio::post(i, std::forward<TFunc>(func));
}

#endif // #if (CC_TUTORIAL_BOOST_MINOR < 66)

} // namespace boost_wrap

} // namespace cc_tutorial

