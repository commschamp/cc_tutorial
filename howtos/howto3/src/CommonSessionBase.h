#pragma once

#include <vector>
#include <cstdint>

namespace cc_tutorial
{

struct CommonSessionBase
{
    using MsgBuf = std::vector<std::uint8_t>;

    static std::size_t preProcessInput(const std::uint8_t* buf, std::size_t bufLen, MsgBuf& outBuf);
    static void postProcessOutput(MsgBuf& buf);
}; 

}