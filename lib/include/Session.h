#pragma once

#include <memory>
#include <vector>
#include <array>
#include <iostream>
#include <iomanip>
#include <type_traits>

#include "boost_wrap.h"

namespace cc_tutorial
{

class Session
{
public:
    using Ptr = std::unique_ptr<Session>;
    using Socket = boost::asio::ip::tcp::socket;

    explicit Session(boost_wrap::io& io) :
        m_io(io),
        m_socket(io)
    {
    }    

    virtual ~Session() = default;

    void setSocket(Socket&& socket)
    {
        m_socket = std::move(socket);
    }

    // Needs to be implemented inside every tutorial
    static Ptr createServer(boost_wrap::io& io);
    static Ptr createClient(boost_wrap::io& io);

    bool start();

    using TerminateCb = std::function<void ()>;
    template <typename TFunc>
    void setTerminateCb(TFunc&& func)
    {
        m_terminateCb = std::forward<TFunc>(func);
    }
    
    boost_wrap::io& getIo()
    {
        return m_io;
    }


protected:
    virtual bool startImpl();
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) = 0;

    void sendOutput(const std::uint8_t* buf, std::size_t bufLen);
    void terminateSession();

    // Common functions to print field's contentents
    template <typename TField>
    void printIntField(const TField& field, const std::string& prefix = std::string())
    {
        using ValueType = typename TField::ValueType;
        using CastType = 
            typename std::conditional<
                sizeof(ValueType) == 1U,
                int,
                ValueType   
            >::type;  // Upcast to int 1 byte sizes for proper printing
        std::cout << '\t' << prefix << field.name() << " = " << 
            static_cast<CastType>(field.value()) << '\n';
    }

    template <typename TField>
    static void printEnumField(const TField& field, const std::string& prefix = std::string())
    {
        using UnderlyingType = typename std::underlying_type<typename TField::ValueType>::type;
        using CastType = 
            typename std::conditional<
                sizeof(UnderlyingType) == 1U,
                int,
                UnderlyingType
            >::type; // Upcast to int 1 byte sizes for proper printing

        std::cout << '\t' << prefix << field.name() << " = " << 
            static_cast<CastType>(field.value()) << 
            " (" << field.valueName() << ")\n";
    }

    template <typename TField>
    static void printSetField(const TField& field, const std::string& prefix = std::string())
    {
        std::cout << '\t' << prefix << field.name() << " = 0x" <<
            std::setfill('0') << std::setw(static_cast<int>(field.length() * 2)) <<
            std::hex << static_cast<std::uintmax_t>(field.value()) << std::dec << '\n';

        for (auto idx = 0U; idx < TField::BitIdx_numOfValues; ++idx) {
            auto bitIdx = static_cast<typename TField::BitIdx>(idx);
            const char* bitName = field.bitName(bitIdx);
            if (bitName == nullptr) {
                continue;
            }


            std::cout << "\t\t" << bitName << ": " << std::boolalpha << field.getBitValue(bitIdx) << '\n';
        }
    }

    template <typename TField>
    static bool printOptionalField(const TField& field, const std::string& prefix = std::string())
    {
        std::cout << '\t' << prefix << field.name();

        static const std::string ModeMap[] = {
            /* comms::field::OptionalMode::Tentative */ "tentative",
            /* comms::field::OptionalMode::Exists */ "exists",
            /* comms::field::OptionalMode::Missing */ "missing",
        };
        static const std::size_t ModeMapSize = std::extent<decltype(ModeMap)>::value;
        //static_assert(ModeMapSize == (unsigned)comms::field::OptionalMode::NumOfModes, "Invalid Map");

        auto mapIdx = static_cast<unsigned>(field.getMode());
        if (ModeMapSize <= mapIdx) {
            assert(!"Unexpected mode value, should not happen");
            std::cout << " (unknown)" << std::endl;
            return false;
        }

        std::cout << " (" << ModeMap[mapIdx] << ")" << std::endl;
        return field.doesExist(); // Print the rest only if field is present
    }    

    template <typename TField>
    static void printString(const TField& field)
    {
        std::cout << '\t' << field.name() << " = " << std::string(field.value().begin(), field.value().end()) << '\n';
    }

    template <typename TField>
    static void printDataField(const TField& field, const std::string& prefix = std::string())
    {
        std::cout << '\t' << prefix << field.name() << " = " << std::hex;
        std::copy(field.value().begin(), field.value().end(), std::ostream_iterator<unsigned>(std::cout, " "));
        std::cout << std::dec << '\n';
    }
    

private:
    void doRead();

    boost_wrap::io& m_io;
    Socket m_socket;
    std::array<std::uint8_t, 1024> m_inBuf;
    std::vector<std::uint8_t> m_inData;
    TerminateCb m_terminateCb;
};

using SessionPtr = std::unique_ptr<Session>;

} // namespace cc_tutorial
