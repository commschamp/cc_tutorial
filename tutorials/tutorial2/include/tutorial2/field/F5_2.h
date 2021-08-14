// Generated by commsdsl2comms v3.6.4

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

    /// @brief Default constructor.
    F5_2()
    {
        Base::value() = std::numeric_limits<ValueType>::quiet_NaN();
    }
    
    /// @brief Special value <b>"S3"</b>.
    static constexpr ValueType valueS3()
    {
        return tutorial2::field::F5_2Common::valueS3();
    }
    
    /// @brief Check the value is equal to special @ref valueS3().
    bool isS3() const
    {
        return ((Base::value() < 0) &&
                (std::isinf(Base::value())));
    }
    
    /// @brief Assign special value @ref valueS3() to the field.
    void setS3()
    {
        Base::value() = valueS3();
    }
    
    /// @brief Special value <b>"S4"</b>.
    static constexpr ValueType valueS4()
    {
        return tutorial2::field::F5_2Common::valueS4();
    }
    
    /// @brief Check the value is equal to special @ref valueS4().
    bool isS4() const
    {
        return (std::abs(Base::value() - static_cast<ValueType>(5.123000)) < std::numeric_limits<ValueType>::epsilon());
    }
    
    /// @brief Assign special value @ref valueS4() to the field.
    void setS4()
    {
        Base::value() = valueS4();
    }
    
    /// @brief Special value <b>"S2"</b>.
    static constexpr ValueType valueS2()
    {
        return tutorial2::field::F5_2Common::valueS2();
    }
    
    /// @brief Check the value is equal to special @ref valueS2().
    bool isS2() const
    {
        return ((0 < Base::value()) &&
                (std::isinf(Base::value())));
    }
    
    /// @brief Assign special value @ref valueS2() to the field.
    void setS2()
    {
        Base::value() = valueS2();
    }
    
    /// @brief Special value <b>"S1"</b>.
    static constexpr ValueType valueS1()
    {
        return tutorial2::field::F5_2Common::valueS1();
    }
    
    /// @brief Check the value is equal to special @ref valueS1().
    bool isS1() const
    {
        return (std::isnan(Base::value()));
    }
    
    /// @brief Assign special value @ref valueS1() to the field.
    void setS1()
    {
        Base::value() = valueS1();
    }
    
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial2::field::F5_2Common::name();
    }
    
};

} // namespace field

} // namespace tutorial2


