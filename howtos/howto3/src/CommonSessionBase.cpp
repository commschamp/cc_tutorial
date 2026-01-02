#include "CommonSessionBase.h"

#include <iterator>
#include <algorithm>

namespace cc_tutorial
{

namespace
{

const std::uint8_t StartByte = 0x02;
const std::uint8_t EndByte = 0x03;
const std::uint8_t EscByte = 0x10;

}

void CommonSessionBase::dropEscapes(const std::uint8_t* buf, std::size_t bufLen, MsgBuf& outBuf)
{
    std::size_t pos = 0U;
    bool escaped = false;
    while (pos < bufLen) {
        auto ch = buf[pos];
        ++pos;

        if ((ch == EscByte) && (!escaped)) {
            escaped = true;
            continue;
        }

        escaped = false;
        outBuf.push_back(ch);
    }
}

void CommonSessionBase::addEscapes(MsgBuf& buf)
{
    MsgBuf newBuf;
    for (auto ch : buf) {
        static const std::uint8_t Special[] = {
            StartByte,
            EndByte,
            EscByte
        };

        auto specialIter = std::find(std::begin(Special), std::end(Special), ch);
        if (specialIter != std::end(Special)) {
            newBuf.push_back(EscByte);
        }

        newBuf.push_back(ch);
    }

    buf.swap(newBuf);
}

}