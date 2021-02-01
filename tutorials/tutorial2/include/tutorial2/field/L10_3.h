// Generated by commsdsl2comms v3.6.0

/// @file
/// @brief Contains definition of <b>"L10_3"</b> field.

#pragma once

#include <cstdint>
#include <tuple>
#include "comms/field/ArrayList.h"
#include "comms/field/Bundle.h"
#include "comms/field/IntValue.h"
#include "comms/field/String.h"
#include "comms/options.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/field/L10_3Common.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Scope for all the member fields of
///     @ref L10_3 list.
/// @tparam TOpt Protocol options.
template <typename TOpt = tutorial2::options::DefaultOptions>
struct L10_3Members
{
    /// @brief Scope for all the member fields of
    ///     @ref Element bundle.
    struct ElementMembers
    {
        /// @brief Definition of <b>"M1"</b> field.
        struct M1 : public
            comms::field::IntValue<
                tutorial2::field::FieldBase<>,
                std::uint8_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::field::L10_3MembersCommon::ElementMembersCommon::M1Common::name();
            }
            
        };
        
        /// @brief Definition of <b>"M2"</b> field.
        struct M2 : public
            comms::field::String<
                tutorial2::field::FieldBase<>,
                typename TOpt::field::L10_3Members::ElementMembers::M2,
                comms::option::def::SequenceFixedSize<3U>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return tutorial2::field::L10_3MembersCommon::ElementMembersCommon::M2Common::name();
            }
            
        };
        
        /// @brief All members bundled in @b std::tuple.
        using All =
            std::tuple<
               M1,
               M2
            >;
    };
    
    /// @brief Definition of <b>"Element"</b> field.
    class Element : public
        comms::field::Bundle<
            tutorial2::field::FieldBase<>,
            typename ElementMembers::All
        >
    {
        using Base = 
            comms::field::Bundle<
                tutorial2::field::FieldBase<>,
                typename ElementMembers::All
            >;
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_NAMES macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        ///
        ///     The generated access types and functions functions are:
        ///     @li @b Field_m1type and @b field_m1() access function -
        ///         for ElementMembers::M1 member field.
        ///     @li @b Field_m2type and @b field_m2() access function -
        ///         for ElementMembers::M2 member field.
        COMMS_FIELD_MEMBERS_NAMES(
            m1,
            m2
        );
        
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_3MembersCommon::ElementCommon::name();
        }
        
    };
    
    /// @brief Definition of <b>"Length"</b> field.
    struct Length : public
        comms::field::IntValue<
            tutorial2::field::FieldBase<>,
            std::uint16_t
        >
    {
        /// @brief Name of the field.
        static const char* name()
        {
            return tutorial2::field::L10_3MembersCommon::LengthCommon::name();
        }
        
    };
    
};

/// @brief Definition of <b>"L10_3"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
struct L10_3 : public
    comms::field::ArrayList<
        tutorial2::field::FieldBase<>,
        typename L10_3Members<TOpt>::Element,
        TExtraOpts...,
        typename TOpt::field::L10_3,
        comms::option::def::SequenceSerLengthFieldPrefix<typename L10_3Members<TOpt>::Length>
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::L10_3Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2


