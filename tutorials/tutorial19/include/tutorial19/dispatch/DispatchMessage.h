// Generated by commsdsl2comms v4.0.1

/// @file
/// @brief Contains dispatch to handling function(s) for all input messages.

#pragma once

#include "tutorial19/MsgId.h"
#include "tutorial19/input/AllMessages.h"
#include "tutorial19/options/DefaultOptions.h"

namespace tutorial19
{

namespace dispatch
{

/// @brief Dispatch message object to its appropriate handling function.
/// @details @b switch statement based (on message ID) cast and dispatch functionality.
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref tutorial19::options::DefaultOptions.
/// @param[in] id Numeric message ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object. Must define
///     @b handle() member function for every message type it exects
///     to handle and one for the interface class as well.
///     @code
///     using MyInterface = tutorial19::Interface<...>;
///     using MyMsg1 = tutorial19::message::Msg1<MyInterface, tutorial19::options::DefaultOptions>;
///     using MyMsg2 = tutorial19::message::Msg2<MyInterface, tutorial19::options::DefaultOptions>;
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
/// @note Defined in tutorial19/dispatch/DispatchMessage.h
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchMessage(
    tutorial19::MsgId id,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    using InterfaceType = typename std::decay<decltype(msg)>::type;
    switch(id) {
    case tutorial19::MsgId_M1:
    {
        using MsgType = tutorial19::message::Msg1<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    case tutorial19::MsgId_M2:
    {
        using MsgType = tutorial19::message::Msg2<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    case tutorial19::MsgId_M3:
    {
        using MsgType = tutorial19::message::Msg3<InterfaceType, TProtOptions>;
        return handler.handle(static_cast<MsgType&>(msg));
    }
    default:
        break;
    };

    return handler.handle(msg);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchMessage(), but receives extra @b idx parameter.
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref tutorial19::options::DefaultOptions.
/// @param[in] id Numeric message ID.
/// @param[in] idx Index of the message among messages with the same ID.
///     Expected to be @b 0.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchMessage()
/// @note Defined in tutorial19/dispatch/DispatchMessage.h
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchMessage(
    tutorial19::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    if (idx != 0U) {
        return handler.handle(msg);
    }
    return dispatchMessage<TProtOptions>(id, msg, handler);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchMessage(), but passing
///     tutorial19::options::DefaultOptions as first template parameter.
/// @param[in] id Numeric message ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchMessage()
/// @note Defined in tutorial19/dispatch/DispatchMessage.h
template<typename TMsg, typename THandler>
auto dispatchMessageDefaultOptions(
    tutorial19::MsgId id,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    return dispatchMessage<tutorial19::options::DefaultOptions>(id, msg, handler);
}

/// @brief Dispatch message object to its appropriate handling function.
/// @details Same as other dispatchMessageDefaultOptions(), 
///     but receives extra @b idx parameter.
/// @param[in] id Numeric message ID.
/// @param[in] idx Index of the message among messages with the same ID.
/// @param[in] msg Message object held by reference to its interface class.
/// @param[in] handler Reference to handling object.
/// @see dispatchMessageDefaultOptions()
/// @note Defined in tutorial19/dispatch/DispatchMessage.h
template<typename TMsg, typename THandler>
auto dispatchMessageDefaultOptions(
    tutorial19::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    return dispatchMessage<tutorial19::options::DefaultOptions>(id, idx, msg, handler);
}

/// @brief Message dispatcher class to be used with
///     @b comms::processAllWithDispatchViaDispatcher() function (or similar).
/// @tparam TProtOptions Protocol options struct used for the application,
///     like @ref tutorial19::options::DefaultOptions.
/// @headerfile tutorial19/dispatch/DispatchMessage.h
template <typename TProtOptions>
struct MsgDispatcher
{
    /// @brief Class detection tag
    using MsgDispatcherTag = void;

    /// @brief Dispatch message to its handler.
    /// @details Uses appropriate @ref dispatchMessage() function.
    /// @param[in] id ID of the message.
    /// @param[in] idx Index (or offset) of the message among those having the same numeric ID.
    /// @param[in] msg Reference to message object.
    /// @param[in] handler Reference to handler object.
    /// @return What the @ref dispatchMessage() function returns.
    template <typename TMsg, typename THandler>
    static auto dispatch(tutorial19::MsgId id, std::size_t idx, TMsg& msg, THandler& handler) ->
        decltype(tutorial19::dispatch::dispatchMessage<TProtOptions>(id, idx, msg, handler))
    {
        return tutorial19::dispatch::dispatchMessage<TProtOptions>(id, idx, msg, handler);
    }

    /// @brief Complementary dispatch function.
    /// @details Same as other dispatch without @b TAllMessages template parameter,
    ///     used by  @b comms::processAllWithDispatchViaDispatcher().
    template <typename TAllMessages, typename TMsg, typename THandler>
    static auto dispatch(tutorial19::MsgId id, std::size_t idx, TMsg& msg, THandler& handler) ->
        decltype(dispatch(id, idx, msg, handler))
    {
        return dispatch(id, idx, msg, handler);
    }

    /// @brief Dispatch message to its handler.
    /// @details Uses appropriate @ref dispatchMessage() function.
    /// @param[in] id ID of the message.
    /// @param[in] msg Reference to message object.
    /// @param[in] handler Reference to handler object.
    /// @return What the @ref dispatchMessage() function returns.
    template <typename TMsg, typename THandler>
    static auto dispatch(tutorial19::MsgId id, TMsg& msg, THandler& handler) ->
        decltype(tutorial19::dispatch::dispatchMessage<TProtOptions>(id, msg, handler))
    {
        return tutorial19::dispatch::dispatchMessage<TProtOptions>(id, msg, handler);
    }

    /// @brief Complementary dispatch function.
    /// @details Same as other dispatch without @b TAllMessages template parameter,
    ///     used by  @b comms::processAllWithDispatchViaDispatcher().
    template <typename TAllMessages, typename TMsg, typename THandler>
    static auto dispatch(tutorial19::MsgId id, TMsg& msg, THandler& handler) ->
        decltype(dispatch(id, msg, handler))
    {
        return dispatch(id, msg, handler);
    }
};

/// @brief Message dispatcher class to be used with
///     @b comms::processAllWithDispatchViaDispatcher() function (or similar).
/// @details Same as @ref MsgDispatcher, but passing
///     @ref tutorial19::options::DefaultOptions as template parameter.
/// @note Defined in tutorial19/dispatch/DispatchMessage.h
using MsgDispatcherDefaultOptions =
    MsgDispatcher<tutorial19::options::DefaultOptions>;



} // namespace dispatch

} // namespace tutorial19
