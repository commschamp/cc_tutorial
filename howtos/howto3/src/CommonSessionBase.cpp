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


std::size_t findMsgStart(const std::uint8_t* buf, std::size_t bufLen)    
{
    std::size_t pos = 0;
    bool escaped = false;
    while (pos < bufLen) {
        auto ch = buf[pos];
        if ((ch == StartByte) && (!escaped)) {
            break;
        }

        ++pos;        

        if ((ch == EscByte) && (!escaped)) {
            escaped = true;
            continue;
        }
            
        escaped = false;
    }

    return pos;
}

std::size_t findMsgEnd(const std::uint8_t* buf, std::size_t bufLen, std::size_t from)    
{
    auto pos = from;
    bool escaped = false;
    while (pos < bufLen) {
        auto ch = buf[pos];
        if ((ch == EndByte) && (!escaped)) {
            break;
        }

        ++pos;        

        if ((ch == EscByte) && (!escaped)) {
            escaped = true;
            continue;
        }
            
        escaped = false;
    }

    return pos;
}

void copyMsg(
    const std::uint8_t* buf, 
    std::size_t startPos, 
    std::size_t endPos, 
    CommonSessionBase::MsgBuf& outBuf)
{
    auto pos = startPos + 1;
    bool escaped = false;
    while (pos < endPos) {
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

}    

std::size_t CommonSessionBase::preProcessInput(
    const std::uint8_t* buf, 
    std::size_t bufLen,
    MsgBuf& outBuf)
{
    outBuf.clear();
    auto startPos = findMsgStart(buf, bufLen);
    if (bufLen <= startPos) {
        // No start has been found, report consumed all input data
        return bufLen; 
    }

    auto endPos = findMsgEnd(buf, bufLen, startPos);
    if (bufLen <= endPos) {
        // No end has been found, report consumed until start
        return startPos; 
    }

    outBuf.reserve(endPos - startPos);
    copyMsg(buf, startPos, endPos, outBuf);
    return endPos + 1;
}

void CommonSessionBase::postProcessOutput(MsgBuf& buf)
{
    MsgBuf newBuf;
    newBuf.push_back(StartByte);
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
    newBuf.push_back(EndByte);
    buf.swap(newBuf);
}

}