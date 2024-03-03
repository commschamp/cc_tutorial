// Generated by commsdsl2comms v6.3.0

/// @file
/// @brief Contains message factory with dynamic memory allocation for all the messages.

#pragma once

#include <memory>
#include "comms/MsgFactoryCreateFailureReason.h"
#include "tutorial2/input/AllMessages.h"

namespace tutorial2
{

namespace factory
{

/// @brief Message factory with dynamic memory allocation for all the messages.
/// @details Defines the same public interface as @b comms::MsgFactory and intended for
///     its replacement.
/// @tparam TInterface Interface class of the messages.
/// @tparam TProtOptions Application specific protocol definition options.
template<typename TInterface, typename TProtOptions>
class AllMessagesDynMemMsgFactory
{
public:
    /// @brief Type of the common base class of all the messages.
    using Message = TInterface;

    /// @brief Type of the message ID when passed as a parameter.
    using MsgIdParamType = typename Message::MsgIdParamType;

    /// @brief Type of the message ID.
    using MsgIdType = typename Message::MsgIdType;

    /// @brief Smart pointer to @ref Message which holds allocated message object.
    using MsgPtr = std::unique_ptr<Message>;

    /// @brief Reason for message creation failure
    using CreateFailureReason = comms::MsgFactoryCreateFailureReason;

    /// @brief Type of generic message.
    /// @details Not supported
    using GenericMessage = void;

    /// @brief Create message object given the ID of the message.
    /// @param id ID of the message.
    /// @param idx Relative index (or offset) of the message with the same ID.
    /// @param[out] reason Failure reason in case creation has failed.
    MsgPtr createMsg(MsgIdParamType id, unsigned idx = 0U, CreateFailureReason* reason = nullptr) const
    {
        auto updateReasonFunc =
            [reason](CreateFailureReason val)
            {
                if (reason != nullptr) {
                    *reason = val;
                }
            };

        if (1U <= idx) {
            updateReasonFunc(CreateFailureReason::InvalidId);
            return MsgPtr();
        }

        updateReasonFunc(CreateFailureReason::None);
        switch (id) {
            case tutorial2::MsgId_M1: return MsgPtr(new tutorial2::message::Msg1<TInterface, TProtOptions>);
            case tutorial2::MsgId_M2: return MsgPtr(new tutorial2::message::Msg2<TInterface, TProtOptions>);
            case tutorial2::MsgId_M3: return MsgPtr(new tutorial2::message::Msg3<TInterface, TProtOptions>);
            case tutorial2::MsgId_M4: return MsgPtr(new tutorial2::message::Msg4<TInterface, TProtOptions>);
            case tutorial2::MsgId_M5: return MsgPtr(new tutorial2::message::Msg5<TInterface, TProtOptions>);
            case tutorial2::MsgId_M6: return MsgPtr(new tutorial2::message::Msg6<TInterface, TProtOptions>);
            case tutorial2::MsgId_M7: return MsgPtr(new tutorial2::message::Msg7<TInterface, TProtOptions>);
            case tutorial2::MsgId_M8: return MsgPtr(new tutorial2::message::Msg8<TInterface, TProtOptions>);
            case tutorial2::MsgId_M9: return MsgPtr(new tutorial2::message::Msg9<TInterface, TProtOptions>);
            case tutorial2::MsgId_M10: return MsgPtr(new tutorial2::message::Msg10<TInterface, TProtOptions>);
            case tutorial2::MsgId_M11: return MsgPtr(new tutorial2::message::Msg11<TInterface, TProtOptions>);
            case tutorial2::MsgId_M12: return MsgPtr(new tutorial2::message::Msg12<TInterface, TProtOptions>);
            case tutorial2::MsgId_M13: return MsgPtr(new tutorial2::message::Msg13<TInterface, TProtOptions>);
            case tutorial2::MsgId_M14: return MsgPtr(new tutorial2::message::Msg14<TInterface, TProtOptions>);
            case tutorial2::MsgId_M15: return MsgPtr(new tutorial2::message::Msg15<TInterface, TProtOptions>);
            case tutorial2::MsgId_M16: return MsgPtr(new tutorial2::message::Msg16<TInterface, TProtOptions>);
            case tutorial2::MsgId_M17: return MsgPtr(new tutorial2::message::Msg17<TInterface, TProtOptions>);
            case tutorial2::MsgId_M18: return MsgPtr(new tutorial2::message::Msg18<TInterface, TProtOptions>);
            default: break;
        }

        updateReasonFunc(CreateFailureReason::InvalidId);
        return MsgPtr();
    }

    /// @brief Allocate and initialise @b comms::GenericMessage object.
    MsgPtr createGenericMsg(MsgIdParamType id, unsigned idx = 0U) const
    {
        static_cast<void>(id);
        static_cast<void>(idx);
        return MsgPtr();
    }

    /// @brief Inquiry whether allocation is possible
    bool canAllocate() const
    {
        return true;
    }

    /// @brief Get number of message types that have the specified ID.
    /// @param id ID of the message.
    /// @return Number of message classes that report same ID.
    std::size_t msgCount(MsgIdParamType id) const
    {
        switch (id)
        {
            case tutorial2::MsgId_M1: return 1U;
            case tutorial2::MsgId_M2: return 1U;
            case tutorial2::MsgId_M3: return 1U;
            case tutorial2::MsgId_M4: return 1U;
            case tutorial2::MsgId_M5: return 1U;
            case tutorial2::MsgId_M6: return 1U;
            case tutorial2::MsgId_M7: return 1U;
            case tutorial2::MsgId_M8: return 1U;
            case tutorial2::MsgId_M9: return 1U;
            case tutorial2::MsgId_M10: return 1U;
            case tutorial2::MsgId_M11: return 1U;
            case tutorial2::MsgId_M12: return 1U;
            case tutorial2::MsgId_M13: return 1U;
            case tutorial2::MsgId_M14: return 1U;
            case tutorial2::MsgId_M15: return 1U;
            case tutorial2::MsgId_M16: return 1U;
            case tutorial2::MsgId_M17: return 1U;
            case tutorial2::MsgId_M18: return 1U;
            default: break;
        }

        return 0U;
    }

    /// @brief Compile time inquiry whether all the message classes have unique IDs.
    static constexpr bool hasUniqueIds()
    {
        return true;
    }

    /// @brief Compile time inquiry whether polymorphic dispatch tables are
    ///     generated internally to map message ID to actual type.
    static constexpr bool isDispatchPolymorphic()
    {
        return false;
    }

    /// @brief Compile time inquiry whether static binary search dispatch is
    ///     generated internally to map message ID to actual type.
    static constexpr bool isDispatchStaticBinSearch()
    {
        return false;
    }

    /// @brief Compile time inquiry whether linear switch dispatch is
    ///     generated internally to map message ID to actual type.
    static constexpr bool isDispatchLinearSwitch()
    {
        return false;
    }

    /// @brief Compile time inquiry whether factory supports in-place allocation
    static constexpr bool hasInPlaceAllocation()
    {
        return false;
    }

    /// @brief Compile time inquiry whether factory supports @b comms::GenericMessage allocation.
    static constexpr bool hasGenericMessageSupport()
    {
        return false;
    }

    /// @brief Compile time inquiry whether factory has forced dispatch method
    static constexpr bool hasForcedDispatch()
    {
        return true;
    }
};

} // namespace factory

} // namespace tutorial2
