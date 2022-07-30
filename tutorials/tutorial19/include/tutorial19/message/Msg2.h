// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of <b>"Message 2"</b> message and its fields.

#pragma once

#include <tuple>
#include "comms/MessageBase.h"
#include "comms/field/EnumValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial19/MsgId.h"
#include "tutorial19/field/FieldBase.h"
#include "tutorial19/message/Msg2Common.h"
#include "tutorial19/options/DefaultOptions.h"


namespace tutorial19
{

namespace message
{


/// @brief Fields of @ref Msg2.
/// @tparam TOpt Extra options
/// @see @ref Msg2
/// @headerfile tutorial19/message/Msg2.h
template <typename TOpt = tutorial19::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Inner field of @ref F1 optional.
    /// @see @ref tutorial19::message::Msg2FieldsCommon::F1Common::ValueType
    class F1Field : public
        comms::field::EnumValue<
            tutorial19::field::FieldBase<>,
            tutorial19::message::Msg2FieldsCommon::F1Common::ValueType,
            comms::option::def::ValidNumValueRange<0, 2>
        >
    {
        using Base =
            comms::field::EnumValue<
                tutorial19::field::FieldBase<>,
                tutorial19::message::Msg2FieldsCommon::F1Common::ValueType,
                comms::option::def::ValidNumValueRange<0, 2>
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Single value name info entry.
        using ValueNameInfo = tutorial19::message::Msg2FieldsCommon::F1Common::ValueNameInfo;
        
        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @see @ref tutorial19::message::Msg2FieldsCommon::F1Common::ValueNamesMapInfo.
        using ValueNamesMapInfo = tutorial19::message::Msg2FieldsCommon::F1Common::ValueNamesMapInfo;
        
        /// @brief Retrieve name of the enum value.
        /// @see @ref tutorial19::message::Msg2FieldsCommon::F1Common::valueName().
        static const char* valueName(ValueType val)
        {
            return tutorial19::message::Msg2FieldsCommon::F1Common::valueName(val);
        }
        
        /// @brief Retrieve name of the @b current value
        const char* valueName() const
        {
            return valueName(Base::getValue());
        }
        
        /// @brief Retrieve map of enum value names.
        /// @see @ref tutorial19::message::Msg2FieldsCommon::F1Common::valueNamesMap().
        static ValueNamesMapInfo valueNamesMap()
        {
            return tutorial19::message::Msg2FieldsCommon::F1Common::valueNamesMap();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial19::message::Msg2FieldsCommon::F1Common::name();
        }
        
    
    };
    
    /// @brief Definition of version dependent
    ///     <b>F1</b> field.
    struct F1 : public
        comms::field::Optional<
            F1Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<1U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F1Field::name();
        }
    };
    
    
    /// @brief Inner field of @ref F2 optional.
    /// @see @ref tutorial19::message::Msg2FieldsCommon::F2Common::ValueType
    class F2Field : public
        comms::field::EnumValue<
            tutorial19::field::FieldBase<>,
            tutorial19::message::Msg2FieldsCommon::F2Common::ValueType,
            comms::option::def::VersionStorage,
            comms::option::def::InvalidByDefault
        >
    {
        using Base =
            comms::field::EnumValue<
                tutorial19::field::FieldBase<>,
                tutorial19::message::Msg2FieldsCommon::F2Common::ValueType,
                comms::option::def::VersionStorage,
                comms::option::def::InvalidByDefault
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Single value name info entry.
        using ValueNameInfo = tutorial19::message::Msg2FieldsCommon::F2Common::ValueNameInfo;
        
        /// @brief Type returned from @ref valueNamesMap() member function.
        /// @see @ref tutorial19::message::Msg2FieldsCommon::F2Common::ValueNamesMapInfo.
        using ValueNamesMapInfo = tutorial19::message::Msg2FieldsCommon::F2Common::ValueNamesMapInfo;
        
        /// @brief Retrieve name of the enum value.
        /// @see @ref tutorial19::message::Msg2FieldsCommon::F2Common::valueName().
        static const char* valueName(ValueType val)
        {
            return tutorial19::message::Msg2FieldsCommon::F2Common::valueName(val);
        }
        
        /// @brief Retrieve name of the @b current value
        const char* valueName() const
        {
            return valueName(Base::getValue());
        }
        
        /// @brief Retrieve map of enum value names.
        /// @see @ref tutorial19::message::Msg2FieldsCommon::F2Common::valueNamesMap().
        static ValueNamesMapInfo valueNamesMap()
        {
            return tutorial19::message::Msg2FieldsCommon::F2Common::valueNamesMap();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial19::message::Msg2FieldsCommon::F2Common::name();
        }
        
        /// @brief Generated validity check functionality.
        bool valid() const
        {
            if (Base::valid()) {
                return true;
            }
            
            if (3U <= Base::getVersion()) {
                if (Base::getValue() == static_cast<typename Base::ValueType>(0)) {
                    return true;
                }
            }
            
            if ((4U <= Base::getVersion()) &&
                (Base::getVersion() < 5U)) {
                if (Base::getValue() == static_cast<typename Base::ValueType>(1)) {
                    return true;
                }
            }
            
            if (5U <= Base::getVersion()) {
                if (Base::getValue() == static_cast<typename Base::ValueType>(2)) {
                    return true;
                }
            }
            
            return false;
            
        }
        
        
    
    };
    
    /// @brief Definition of version dependent
    ///     <b>F2</b> field.
    struct F2 : public
        comms::field::Optional<
            F2Field,
            comms::option::def::ExistsByDefault,
            comms::option::def::ExistsSinceVersion<3U>
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return F2Field::name();
        }
    };
    
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        F1,
        F2
    >;
};

/// @brief Definition of <b>"Message 2"</b> message class.
/// @details
///     See @ref Msg2Fields for definition of the fields this message contains.
/// @tparam TMsgBase Base (interface) class.
/// @tparam TOpt Extra options
/// @headerfile tutorial19/message/Msg2.h
template <typename TMsgBase, typename TOpt = tutorial19::options::DefaultOptions>
class Msg2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial19::MsgId_M2>,
        comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
        comms::option::def::HasName
    >
{
    // Redefinition of the base class type
    using Base =
        comms::MessageBase<
            TMsgBase,
            comms::option::def::StaticNumIdImpl<tutorial19::MsgId_M2>,
            comms::option::def::FieldsImpl<typename Msg2Fields<TOpt>::All>,
            comms::option::def::MsgType<Msg2<TMsgBase, TOpt> >,
            comms::option::def::HasName
        >;

public:
    /// @brief Provide names and allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_NAMES macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and functions are:
    ///     @li @b FieldIdx_f1 index, @b Field_f1 type and @b field_f1() access fuction
    ///         for @ref Msg2Fields::F1 field.
    ///     @li @b FieldIdx_f2 index, @b Field_f2 type and @b field_f2() access fuction
    ///         for @ref Msg2Fields::F2 field.
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );
    
    // Compile time check for serialisation length.
    static const std::size_t MsgMinLen = Base::doMinLength();
    static const std::size_t MsgMaxLen = Base::doMaxLength();
    static_assert(MsgMinLen == 0U, "Unexpected min serialisation length");
    static_assert(MsgMaxLen == 2U, "Unexpected max serialisation length");
    
    /// @brief Name of the message.
    static const char* doName()
    {
        return tutorial19::message::Msg2Common::name();
    }
    

};

} // namespace message

} // namespace tutorial19


