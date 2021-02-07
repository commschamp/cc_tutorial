// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of <b>"Message 1"</b> message and its fields.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/BitmaskValue.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial14/MsgId.h"
#include "tutorial14/field/FieldBase.h"
#include "tutorial14/message/Msg1Common.h"
#include "tutorial14/options/DefaultOptions.h"

namespace tutorial14
{

namespace message
{

/// @brief Fields of @ref Msg1.
/// @tparam TOpt Extra options
/// @see @ref Msg1
/// @headerfile "tutorial14/message/Msg1.h"
template <typename TOpt = tutorial14::options::DefaultOptions>
struct Msg1Fields
{
    /// @brief Scope for all the member fields of
    ///     @ref F1 optional.
    struct F1Members
    {
        /// @brief Definition of <b>"F1"</b> field.
        struct F1 : public
            comms::field::IntValue<
                tutorial14::field::FieldBase<>,
                std::uint32_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial14::message::Msg1FieldsCommon::F1MembersCommon::F1Common::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F1"</b> field.
    struct F1 : public
        comms::field::Optional<
            typename F1Members::F1,
            comms::option::def::ExistsByDefault
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial14::message::Msg1FieldsCommon::F1Common::name();
        }
        
    };
    
    /// @brief Scope for all the member fields of
    ///     @ref F2 optional.
    struct F2Members
    {
        /// @brief Definition of <b>"F2"</b> field.
        struct F2 : public
            comms::field::IntValue<
                tutorial14::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial14::message::Msg1FieldsCommon::F2MembersCommon::F2Common::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F2"</b> field.
    struct F2 : public
        comms::field::Optional<
            typename F2Members::F2,
            comms::option::def::MissingByDefault
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial14::message::Msg1FieldsCommon::F2Common::name();
        }
        
    };
    
    /// @brief Scope for all the member fields of
    ///     @ref F3 optional.
    struct F3Members
    {
        /// @brief Definition of <b>"F3"</b> field.
        struct F3 : public
            comms::field::IntValue<
                tutorial14::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial14::message::Msg1FieldsCommon::F3MembersCommon::F3Common::name();
            }
            
        };
        
    };
    
    /// @brief Definition of <b>"F3"</b> field.
    struct F3 : public
        comms::field::Optional<
            typename F3Members::F3,
            comms::option::def::MissingByDefault
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial14::message::Msg1FieldsCommon::F3Common::name();
        }
        
    };
    
    /// @brief Definition of <b>"Flags"</b> field.
    class Flags : public
        comms::field::BitmaskValue<
            tutorial14::field::FieldBase<>,
            comms::option::def::FixedLength<1U>,
            comms::option::def::BitmaskReservedBits<0xFEU, 0x0U>
        >
    {
        using Base = 
            comms::field::BitmaskValue<
                tutorial14::field::FieldBase<>,
                comms::option::def::FixedLength<1U>,
                comms::option::def::BitmaskReservedBits<0xFEU, 0x0U>
            >;
    public:
        /// @brief Provides names and generates access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        ///
        ///      The generated enum values and functions are:
        ///      @li @b BitIdx_F2F3, @b getBitValue_F2F3() and @b setBitValue_F2F3().
        COMMS_BITMASK_BITS_SEQ(
            F2F3
        );
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial14::message::Msg1FieldsCommon::FlagsCommon::name();
        }
        
        /// @brief Retrieve name of the bit.
        static const char* bitName(BitIdx idx)
        {
            return
                tutorial14::message::Msg1FieldsCommon::FlagsCommon::bitName(
                    static_cast<std::size_t>(idx));
        }
        
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2,
        F3,
        Flags
    >;
};

/// @brief Definition of <b>"Message 1"</b> message class.
/// @details
///     See @ref Msg1Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile "tutorial14/message/Msg1.h"
template <typename TMsgBase, typename TOpt = tutorial14::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial14::MsgId_M1>,
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
            comms::option::def::StaticNumIdImpl<tutorial14::MsgId_M1>,
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
    ///     The generated types and functions are:
    ///     @li @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg1Fields::F1 field.
    ///     @li @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg1Fields::F2 field.
    ///     @li @b Field_f3 type and @b field_f3() access fuction
    ///         for @ref Msg1Fields::F3 field.
    ///     @li @b Field_flags type and @b field_flags() access fuction
    ///         for @ref Msg1Fields::Flags field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2,
        f3,
        flags
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 1U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 9U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial14::message::Msg1Common::name();
    }
    
    /// @brief Custom read functionality
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        field_f1().setExists();
        field_f2().setMissing();
        field_f3().setMissing();
        
        auto es = Base::doRead(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }
    
        if (field_flags().getBitValue_F2F3()) {
            field_f2().field().value() = static_cast<typename Field_f2::Field::ValueType>((field_f1().field().value() >> 16U) & 0xffffU);
            field_f3().field().value() = static_cast<typename Field_f3::Field::ValueType>(field_f1().field().value() & 0xffffU);
            field_f1().setMissing();
            field_f2().setExists();
            field_f3().setExists();
        }
        
        return es;
    }
    
    /// @brief Custom refresh functionality
    bool doRefresh()
    {
        auto f1Mode = comms::field::OptionalMode::Exists;
        auto f2f3Mode = comms::field::OptionalMode::Missing;
        
        if (field_flags().getBitValue_F2F3()) {
            std::swap(f1Mode, f2f3Mode);
        }
    
        bool updated = Base::doRefresh(); // Don't forget default refresh functionality
        
        if (field_f1().getMode() != f1Mode) {
            field_f1().setMode(f1Mode);
            updated = true;
        }
        
        if (field_f2().getMode() != f2f3Mode) {
            field_f2().setMode(f2f3Mode);
            updated = true;
        }
    
        if (field_f3().getMode() != f2f3Mode) {
            field_f3().setMode(f2f3Mode);
            updated = true;
        }
    
        return updated;
    }
    
    
};

} // namespace message

} // namespace tutorial14


