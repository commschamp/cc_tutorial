// Generated by commsdsl2comms v5.0.0

/// @file
/// @brief Contains definition of <b>"Length"</b> field.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/Bundle.h"
#include "comms/field/IntValue.h"
#include "comms/field/Optional.h"
#include "comms/options.h"
#include "tutorial23/field/FieldBase.h"
#include "tutorial23/field/LengthCommon.h"
#include "tutorial23/options/DefaultOptions.h"

namespace tutorial23
{

namespace field
{


/// @brief Scope for all the member fields of
///     @ref Length field.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial23::options::DefaultOptions>
struct LengthMembers
{
    /// @brief Definition of <b>"Short"</b> field.
    class Short : public
        comms::field::IntValue<
            tutorial23::field::FieldBase<>,
            std::uint8_t
        >
    {
        using Base =
            comms::field::IntValue<
                tutorial23::field::FieldBase<>,
                std::uint8_t
            >;
    public:
        /// @brief Re-definition of the value type.
        using ValueType = typename Base::ValueType;
        
        /// @brief Single special value name info entry.
        using SpecialNameInfo = tutorial23::field::LengthMembersCommon::ShortCommon::SpecialNameInfo;
        
        /// @brief Type returned from @ref specialNamesMap() member function.
        /// @details The @b first value of the pair is pointer to the map array,
        ///     The @b second value of the pair is the size of the array.
        using SpecialNamesMapInfo = tutorial23::field::LengthMembersCommon::ShortCommon::SpecialNamesMapInfo;
        
        /// @brief Compile time detection of special values presence.
        static constexpr bool hasSpecials()
        {
            return tutorial23::field::LengthMembersCommon::ShortCommon::hasSpecials();
        }
        
        /// @brief Special value <b>"LongForm"</b>.
        /// @see @ref tutorial23::field::LengthMembersCommon::ShortCommon::valueLongForm().
        static constexpr ValueType valueLongForm()
        {
            return tutorial23::field::LengthMembersCommon::ShortCommon::valueLongForm();
        }
        
        /// @brief Check the value is equal to special @ref valueLongForm().
        bool isLongForm() const
        {
            return Base::getValue() == valueLongForm();
        }
        
        /// @brief Assign special value @ref valueLongForm() to the field.
        void setLongForm()
        {
            Base::setValue(valueLongForm());
        }
        
        /// @brief Retrieve map of special value names
        static SpecialNamesMapInfo specialNamesMap()
        {
            return tutorial23::field::LengthMembersCommon::ShortCommon::specialNamesMap();
        }
        
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial23::field::LengthMembersCommon::ShortCommon::name();
        }
        
    
    };
    
    
    /// @brief Scope for all the member fields of
    ///     @ref Long field.
    struct LongMembers
    {
        /// @brief Definition of <b>"ActLong"</b> field.
        class ActLong : public
            comms::field::IntValue<
                tutorial23::field::FieldBase<>,
                std::uint16_t
            >
        {
            using Base =
                comms::field::IntValue<
                    tutorial23::field::FieldBase<>,
                    std::uint16_t
                >;
        public:
            /// @brief Re-definition of the value type.
            using ValueType = typename Base::ValueType;
            
            /// @brief Compile time detection of special values presence.
            static constexpr bool hasSpecials()
            {
                return tutorial23::field::LengthMembersCommon::LongMembersCommon::ActLongCommon::hasSpecials();
            }
            
            
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial23::field::LengthMembersCommon::LongMembersCommon::ActLongCommon::name();
            }
            
        
        };
        
        
    };
    
    /// @brief Definition of <b>"Long"</b> field.
    class Long : public
        comms::field::Optional<
            typename LongMembers::ActLong,
            comms::option::def::MissingByDefault
        >
    {
        using Base =
            comms::field::Optional<
                typename LongMembers::ActLong,
                comms::option::def::MissingByDefault
            >;
    public:
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial23::field::LengthMembersCommon::LongCommon::name();
        }
        
    
    };
    
    
    /// @brief All members bundled in @b std::tuple.
    using All =
        std::tuple<
           Short,
           Long
        >;
};

/// @brief Definition of <b>"Length"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial23::options::DefaultOptions, typename... TExtraOpts>
class Length : public
    comms::field::Bundle<
        tutorial23::field::FieldBase<>,
        typename LengthMembers<TOpt>::All,
        TExtraOpts...,
        comms::option::def::HasCustomRead,
        comms::option::def::HasCustomRefresh
    >
{
    using Base =
        comms::field::Bundle<
            tutorial23::field::FieldBase<>,
            typename LengthMembers<TOpt>::All,
            TExtraOpts...,
            comms::option::def::HasCustomRead,
            comms::option::def::HasCustomRefresh
        >;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
    ///     related to @b comms::field::Bundle class from COMMS library
    ///     for details.
    ///
    ///     The generated values, types and access functions are:
    ///     @li @b FieldIdx_short index, @b Field_short type and @b field_short() access function -
    ///         for tutorial23::field::LengthMembers::Short member field.
    ///     @li @b FieldIdx_long index, @b Field_long type and @b field_long() access function -
    ///         for tutorial23::field::LengthMembers::Long member field.
    COMMS_FIELD_MEMBERS_NAMES(
        short,
        long
    );
    
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial23::field::LengthCommon::name();
    }
    
    /// @brief Get length value
    std::size_t getValue() const
    {
        if (!field_short().isLongForm()) {
            return static_cast<std::size_t>(field_short().value());
        }
    
        COMMS_ASSERT(field_long().doesExist()); // Make sure the field in the consistent state
        return static_cast<std::size_t>(field_long().field().value());
    }
    
    /// @brief Set length value
    void setValue(std::size_t val)
    {
        if (val < Field_short::valueLongForm()) {
            field_short().setValue(val);
            field_long().setMissing();
            return;
        }
    
        field_short().setLongForm();
        field_long().field().setValue(val);
        field_long().setExists();
    }
    
    /// @brief Maximal possible length value
    static constexpr std::size_t maxValue()
    {
        return std::numeric_limits<typename Field_long::Field::ValueType>::max();
    }
    
    /// @brief Generated read functionality.
    template <typename TIter>
    comms::ErrorStatus read(TIter& iter, std::size_t len)
    {
        auto es = comms::ErrorStatus::Success;
        do {
            es = Base::template readUntilAndUpdateLen<FieldIdx_long>(iter, len);
            if (es != comms::ErrorStatus::Success) {
                break;
            }
            
            readPrepare_long();
            
            es = Base::template readFrom<FieldIdx_long>(iter, len);
            
        } while(false);
        return es;
    }
    
    
    /// @brief Generated refresh functionality.
    bool refresh()
    {
        bool updated = Base::refresh();
        updated = refresh_long() || updated;
        return updated;
        
    }
    
    

private:
    void readPrepare_long()
    {
        refresh_long();
        
    }
    
    bool refresh_long()
    {
        auto mode = comms::field::OptionalMode::Missing;
        if (field_short().getValue() == static_cast<typename Field_short::ValueType>(255U)) {
            mode = comms::field::OptionalMode::Exists;
        }
        
        if (field_long().getMode() == mode) {
            return false;
        }
        
        field_long().setMode(mode);
        return true;
        
    }
    

};


} // namespace field

} // namespace tutorial23

