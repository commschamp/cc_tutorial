// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial20::message::Connect message and its fields.

#pragma once

#include "tutorial20/field/VersionCommon.h"

namespace tutorial20
{

namespace message
{

/// @brief Common types and functions for fields of 
///     @ref tutorial20::message::Connect message.
/// @see tutorial20::message::ConnectFields
struct ConnectFieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref tutorial20::message::ConnectFields::Version field.
    using VersionCommon = tutorial20::field::VersionCommon;
    
};

/// @brief Common types and functions of 
///     @ref tutorial20::message::Connect message.
/// @see tutorial20::message::Connect
struct ConnectCommon
{
    /// @brief Name of the @ref tutorial20::message::Connect message.
    static const char* name()
    {
        return "Connect";
    }
    
};

} // namespace message

} // namespace tutorial20


