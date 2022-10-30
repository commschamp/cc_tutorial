// Generated by commsdsl2comms v5.1.2

/// @file
/// @brief Contains definition of <b>"F5_2"</b> field.

#pragma once

#include <cmath>
#include <limits>
#include "comms/field/FloatValue.h"
#include "comms/options.h"
#include "tutorial2/field/F5_2Common.h"
#include "tutorial2/field/FieldBase.h"
#include "tutorial2/options/DefaultOptions.h"

namespace tutorial2
{

namespace field
{

/// @brief Definition of <b>"F5_2"</b> field.
/// @tparam TOpt Protocol options.
/// @tparam TExtraOpts Extra options.
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class F5_2 : public
    comms::field::FloatValue<
        tutorial2::field::FieldBase<>,
        double,
        TExtraOpts...
    >
{
    using Base =
        comms::field::FloatValue<
            tutorial2::field::FieldBase<>,
            double,
            TExtraOpts...
        >;
public:
    /// @brief Re-definition of the value type.
    using ValueType = typename Base::ValueType;

    /// @brief Single special value name info entry.
    using SpecialNameInfo = tutorial2::field::F5_2Common::SpecialNameInfo;

    /// @brief Type returned from @ref specialNamesMap() member function.
    /// @details The @b first value of the pair is pointer to the map array,
    ///     The @b second value of the pair is the size of the array.
    using SpecialNamesMapInfo = tutorial2::field::F5_2Common::SpecialNamesMapInfo;

    /// @brief Generated default constructor.
    F5_2()
    {
        Base::setValue(std::numeric_limits<ValueType>::quiet_NaN());
    }

    /// @brief Compile time detection of special values presence.
    static constexpr bool hasSpecials()
    {
        return tutorial2::field::F5_2Common::hasSpecials();
    }

    /// @brief Special value <b>"S3"</b>.
    /// @see @ref tutorial2::field::F5_2Common::valueS3().
    static constexpr ValueType valueS3()
    {
        return tutorial2::field::F5_2Common::valueS3();
    }

    /// @brief Check the value is equal to special @ref valueS3().
    bool isS3() const
    {
        return ((Base::getValue() < 0) &&
                (std::isinf(Base::getValue())));
    }

    /// @brief Assign special value @ref valueS3() to the field.
    void setS3()
    {
        Base::setValue(valueS3());
    }

    /// @brief Special value <b>"S4"</b>.
    /// @see @ref tutorial2::field::F5_2Common::valueS4().
    static constexpr ValueType valueS4()
    {
        return tutorial2::field::F5_2Common::valueS4();
    }

    /// @brief Check the value is equal to special @ref valueS4().
    bool isS4() const
    {
        return (std::abs(Base::getValue() - static_cast<ValueType>(5.123000)) < std::numeric_limits<ValueType>::epsilon());
    }

    /// @brief Assign special value @ref valueS4() to the field.
    void setS4()
    {
        Base::setValue(valueS4());
    }

    /// @brief Special value <b>"S2"</b>.
    /// @see @ref tutorial2::field::F5_2Common::valueS2().
    static constexpr ValueType valueS2()
    {
        return tutorial2::field::F5_2Common::valueS2();
    }

    /// @brief Check the value is equal to special @ref valueS2().
    bool isS2() const
    {
        return ((0 < Base::getValue()) &&
                (std::isinf(Base::getValue())));
    }

    /// @brief Assign special value @ref valueS2() to the field.
    void setS2()
    {
        Base::setValue(valueS2());
    }

    /// @brief Special value <b>"S1"</b>.
    /// @see @ref tutorial2::field::F5_2Common::valueS1().
    static constexpr ValueType valueS1()
    {
        return tutorial2::field::F5_2Common::valueS1();
    }

    /// @brief Check the value is equal to special @ref valueS1().
    bool isS1() const
    {
        return (std::isnan(Base::getValue()));
    }

    /// @brief Assign special value @ref valueS1() to the field.
    void setS1()
    {
        Base::setValue(valueS1());
    }

    /// @brief Retrieve map of special value names
    static SpecialNamesMapInfo specialNamesMap()
    {
        return tutorial2::field::F5_2Common::specialNamesMap();
    }

    /// @brief Requested number of digits after decimal point when value
    ///     is displayed.
    static constexpr unsigned displayDecimals()
    {
        return 0U;
    }

    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::F5_2Common::name();
    }
};

} // namespace field

} // namespace tutorial2
