// Generated by commsdsl2comms v6.2.1

/// @file
/// @brief Contains dispatch to handling function(s) for client input input messages.

#pragma once

#include "howto2/MsgId.h"
#include "howto2/input/ServerInputMessages.h"
#include "howto2/options/DefaultOptions.h"

namespace howto2
{

namespace dispatch
{

/// @brief Dispatch message object to its appropriate handling function.
/// @details @b switch statement based (on message ID) cast and dispatch functionality.
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref howto2::options::DefaultOptions.
/// @param[in] id Numeric message ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object. Must define
///     @b handle() member function for every message type it exects
///     to handle and one for the interface class as well.
///     @code
///     using MyInterface = howto2::Message<...>;
///     using MyMsg1 = howto2::message::Msg1<MyInterface, howto2::options::DefaultOptions>;
///     using MyMsg2 = howto2::message::Msg2<MyInterface, howto2::options::DefaultOptions>;
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
/// @note Defined in howto2/dispatch/DispatchServerInputMessage.h
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchServerInputMessage(
    howto2::MsgId id,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    using InterfaceType = typename std::decay<decltype(msg)>::type;
    switch(id) {
    case howto2::MsgId_M1:
    {
        using MsgType = howto2::message::Msg1<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    case howto2::MsgId_M2:
    {
        using MsgType = howto2::message::Msg2<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    case howto2::MsgId_M3:
    {
        using MsgType = howto2::message::Msg3<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    case howto2::MsgId_M4:
    {
        using MsgType = howto2::message::Msg4<InterfaceType, TProtOptions>;
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
///     like @ref howto2::options::DefaultOptions.
/// @param[in] id Numeric message ID.
/// @param[in] idx Index of the message among messages with the same ID.
///     Expected to be @b 0.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchServerInputMessage()
/// @note Defined in howto2/dispatch/DispatchServerInputMessage.h
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchServerInputMessage(
    howto2::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    if (idx != 0U) {
        return handler.handle(msg);
    }
    return dispatchServerInputMessage<TProtOptions>(id, msg, handler);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchServerInputMessage(), but passing
///     howto2::options::DefaultOptions as first template parameter.
/// @param[in] id Numeric message ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchServerInputMessage()
/// @note Defined in howto2/dispatch/DispatchServerInputMessage.h
template<typename TMsg, typename THandler>
auto dispatchServerInputMessageDefaultOptions(
    howto2::MsgId id,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    return dispatchServerInputMessage<howto2::options::DefaultOptions>(id, msg, handler);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchServerInputMessageDefaultOptions(), 
///     but receives extra @b idx parameter.
/// @param[in] id Numeric message ID.
/// @param[in] idx Index of the message among messages with the same ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchServerInputMessageDefaultOptions()
/// @note Defined in howto2/dispatch/DispatchServerInputMessage.h
template<typename TMsg, typename THandler>
auto dispatchServerInputMessageDefaultOptions(
    howto2::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    return dispatchServerInputMessage<howto2::options::DefaultOptions>(id, idx, msg, handler);
}

/// @brief Message dispatcher class to be used with
///     @b comms::processAllWithDispatchViaDispatcher() function (or similar).
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref howto2::options::DefaultOptions.
/// @headerfile howto2/dispatch/DispatchServerInputMessage.h
template <typename TProtOptions = howto2::options::DefaultOptions>
struct ServerInputMsgDispatcher
{
    /// @brief Class detection tag
    using MsgDispatcherTag = void;

    /// @brief Dispatch message to its handler.
    /// @details Uses appropriate @ref dispatchServerInputMessage() function.
    /// @param[in] id ID of the message.
    /// @param[in] idx Index (or offset) of the message among those having the same numeric ID.
    /// @param[in] msg Reference to message object.
    /// @param[in] handler Reference to handler object.
    /// @return What the @ref dispatchServerInputMessage() function returns.
    template <typename TMsg, typename THandler>
    static auto dispatch(howto2::MsgId id, std::size_t idx, TMsg& msg, THandler& handler) ->
        decltype(howto2::dispatch::dispatchServerInputMessage<TProtOptions>(id, idx, msg, handler))
    {
        return howto2::dispatch::dispatchServerInputMessage<TProtOptions>(id, idx, msg, handler);
    }

    /// @brief Complementary dispatch function.
    /// @details Same as other dispatch without @b TAllMessages template parameter,
    ///     used by  @b comms::processAllWithDispatchViaDispatcher().
    template <typename TAllMessages, typename TMsg, typename THandler>
    static auto dispatch(howto2::MsgId id, std::size_t idx, TMsg& msg, THandler& handler) ->
        decltype(dispatch(id, idx, msg, handler))
    {
        return dispatch(id, idx, msg, handler);
    }

    /// @brief Dispatch message to its handler.
    /// @details Uses appropriate @ref dispatchServerInputMessage() function.
    /// @param[in] id ID of the message.
    /// @param[in] msg Reference to message object.
    /// @param[in] handler Reference to handler object.
    /// @return What the @ref dispatchServerInputMessage() function returns.
    template <typename TMsg, typename THandler>
    static auto dispatch(howto2::MsgId id, TMsg& msg, THandler& handler) ->
        decltype(howto2::dispatch::dispatchServerInputMessage<TProtOptions>(id, msg, handler))
    {
        return howto2::dispatch::dispatchServerInputMessage<TProtOptions>(id, msg, handler);
    }

    /// @brief Complementary dispatch function.
    /// @details Same as other dispatch without @b TAllMessages template parameter,
    ///     used by  @b comms::processAllWithDispatchViaDispatcher().
    template <typename TAllMessages, typename TMsg, typename THandler>
    static auto dispatch(howto2::MsgId id, TMsg& msg, THandler& handler) ->
        decltype(dispatch(id, msg, handler))
    {
        return dispatch(id, msg, handler);
    }
};

/// @brief Message dispatcher class to be used with
///     @b comms::processAllWithDispatchViaDispatcher() function (or similar).
/// @details Same as ServerInputMsgDispatcher, but passing
///     @ref howto2::options::DefaultOptions as template parameter.
/// @note Defined in howto2/dispatch/DispatchServerInputMessage.h
using ServerInputMsgDispatcherDefaultOptions =
    ServerInputMsgDispatcher<>;

} // namespace dispatch

} // namespace howto2
