/// @file
/// @brief Contains dispatch to handling function(s) for server input messages.

#pragma once

#include <type_traits>
#include "tutorial1/MsgId.h"
#include "tutorial1/input/ServerInputMessages.h"

namespace tutorial1
{

namespace dispatch
{

/// @brief Dispatch message object to its appropriate handling function.
/// @details @b switch statement based (on message ID) cast and dispatch functionality.
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref tutorial1::options::DefaultOptions.
/// @param[in] id Numeric message ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object. Must define
///     @b handle() member function for every message type it exects
///     to handle and one for the interface class as well.
///     @code
///     using MyInterface = tutorial1::Message<...>;
///     using MyMsg1 = tutorial1::message::Msg1<MyInterface, tutorial1::options::DefaultOptions>;
///     using MyMsg2 = tutorial1::message::Msg2<MyInterface, tutorial1::options::DefaultOptions>;
///     struct MyHandler {
///         void handle(MyMsg1& msg) {...}
///         void handle(MyMsg2& msg) {...}
///         ...
///         // Handle all unexpected or irrelevant messages.
///         void handle(MyInterface& msg) {...}
///     };
///     @endcode
///     Every @b handle() function may return a value, but every
///     function must return the @b same type.
/// @note Defined in tutorial1/dispatch/DispatchServerInputMessage.h
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchServerInputMessage(
    tutorial1::MsgId id,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    using InterfaceType = typename std::decay<decltype(msg)>::type;
    switch(id) {
    case tutorial1::MsgId_M1:
    {
        using MsgType = tutorial1::message::Msg1<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    case tutorial1::MsgId_M2:
    {
        using MsgType = tutorial1::message::Msg2<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    default:
        break;
    };

    return handler.handle(msg);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchServerInputMessage(), but receives extra @b idx parameter.
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref tutorial1::options::DefaultOptions.
/// @param[in] id Numeric message ID.
/// @param[in] idx Index of the message among messages with the same ID.
///     Expected to be @b 0.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchServerInputMessage()
/// @note Defined in tutorial1/dispatch/DispatchServerInputMessage.h
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchServerInputMessage(
    tutorial1::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    if (idx != 0U) {
        return handler.handle(msg);
    }
    return dispatchServerInputMessage(id, msg, handler);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchServerInputMessage(), but passing
///     tutorial1::options::DefaultOptions as first template parameter.
/// @param[in] id Numeric message ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchServerInputMessage()
/// @note Defined in tutorial1/dispatch/DispatchServerInputMessage.h
template<typename TMsg, typename THandler>
auto dispatchServerInputMessageDefaultOptions(
    tutorial1::MsgId id,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    return dispatchServerInputMessage<tutorial1::options::DefaultOptions>(id, msg, handler);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchServerInputMessageDefaultOptions(), 
///     but receives extra @b idx parameter.
/// @param[in] id Numeric message ID.
/// @param[in] idx Index of the message among messages with the same ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchServerInputMessageDefaultOptions()
/// @note Defined in tutorial1/dispatch/DispatchServerInputMessage.h
template<typename TMsg, typename THandler>
auto dispatchServerInputMessageDefaultOptions(
    tutorial1::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    return dispatchServerInputMessage<tutorial1::options::DefaultOptions>(id, idx, msg, handler);
}

} // namespace dispatch

} // namespace tutorial1


