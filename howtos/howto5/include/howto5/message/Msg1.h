// Generated by commsdsl2comms v3.6.4

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "howto5/MsgId.h"
#include "howto5/field/FieldBase.h"
#include "howto5/message/Msg1Common.h"
#include "howto5/options/DefaultOptions.h"

namespace howto5
{

namespace message
{

/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile "howto5/message/Msg1.h"
template <typename TOpt = howto5::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::IntValue<
            howto5::field::FieldBase<>,
            std::uint16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::message::Msg1FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief Scope for all the member fields of
    ///     @ref F2 optional.
    struct F2Members
    {
        /// @brief Definition of <b>"F3"</b> field.
        struct Field : public
            comms::field::IntValue<
                howto5::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return howto5::message::Msg1FieldsCommon::F2MembersCommon::FieldCommon::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F2"</b> field.
    /// @details
    ///     The field exists only when B0 in interface flags is set.
    struct F2 : public
        comms::field::Optional<
            typename F2Members::Field,
            comms::option::def::MissingByDefault
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::message::Msg1FieldsCommon::F2Common::name();
        }
        
    };
    
    /// @brief Inner field of @ref F3 optional.
    struct F3Field : public
        comms::field::IntValue<
            howto5::field::FieldBase<>,
            std::uint16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return howto5::message::Msg1FieldsCommon::F3Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"F3"</b> field.
    struct F3 : public
        comms::field::Optional<
            F3Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<5U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F3Field::name();
        }
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "howto5/message/Msg1.h"
template <typename TMsgBase, typename TOpt = howto5::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<howto5::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::HasCustomRefresh
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<howto5::MsgId_M1>,
            comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
            comms::option::def::HasName,
            comms::option::def::HasCustomRefresh
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg1Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg1Fields::F2 field.
    ///     @li @b FieldIdx_f3 index, @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg1Fields::F3 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 2U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 6U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return howto5::message::Msg1Common::name();
    }
    
    /// @brief Custom read functionality
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        doRefresh(); // Update mode according to flags in the interface
        return Base::doRead(iter, len);
    }
     
    // @brief Custom refresh functionality
    bool doRefresh()
    {
        bool updated = Base::doRefresh(); // Don't forget default refresh functionality
    
        auto expF2Mode = comms::field::OptionalMode::Missing;
        if (Base::transportField_flags().getBitValue_B0()) {
            expF2Mode = comms::field::OptionalMode::Exists;
        }
    
        if (field_f2().getMode() == expF2Mode) {
            return updated;
        }
    
        field_f2().setMode(expF2Mode);
        return true;
    }
    
};

} // namespace message

} // namespace howto5


