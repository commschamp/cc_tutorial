// Generated by commsdsl2comms v6.1.0

/// @file
/// @brief Contains definition of <b>"I1"</b> field.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "t23_ext/field/FieldBase.h"
#include "t23_ext/ns1/field/I1Common.h"
#include "t23_ext/options/DefaultOptions.h"

namespace t23_ext
{

namespace ns1
{

namespace field
{

/// @brief Definition of <b>"I1"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = t23_ext::options::DefaultOptions, typename... TExtraOpts>
class I1 : public
    comms::field::IntValue<
        t23_ext::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...
    >
{
    using Base =
        comms::field::IntValue<
            t23_ext::field::FieldBase<>,
            std::uint16_t,
            TExtraOpts...
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single special value name info entry.
    using SpecialNameInfo = t23_ext::ns1::field::I1Common::SpecialNameInfo;

    /// @brief Type returned from @ref specialNamesMap() member function.
    /// @details The @b first value of the pair is pointer to the map array,
    ///     The @b second value of the pair is the size of the array.
    using SpecialNamesMapInfo = t23_ext::ns1::field::I1Common::SpecialNamesMapInfo;

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return t23_ext::ns1::field::I1Common::hasSpecials();
    }

    /// @brief Special value <b>"S1"</b>.
    /// @see @ref t23_ext::ns1::field::I1Common::valueS1().
    static constexpr ValueType valueS1()
    {
        return t23_ext::ns1::field::I1Common::valueS1();
    }

    /// @brief Check the value is equal to special @ref valueS1().
    bool isS1() const
    {
        return Base::getValue() == valueS1();
    }

    /// @brief Assign special value @ref valueS1() to the field.
    void setS1()
    {
        Base::setValue(valueS1());
    }

    /// @brief Retrieve map of special value names
    static SpecialNamesMapInfo specialNamesMap()
    {
        return t23_ext::ns1::field::I1Common::specialNamesMap();
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return t23_ext::ns1::field::I1Common::name();
    }
};

} // namespace field

} // namespace ns1

} // namespace t23_ext
