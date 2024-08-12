#pragma once

#include <quant/geometry/Scalar.h>
#include <quant/geometry/ScalarState.h>
#include <quant/units/Scalar.h>
#include <quant/units/angular_speed/constants.h>
#include <quant/units/angular_speed/forward_declarations.h>

#include <ostream>

namespace quant::units::angular_speed
{

    class AngularSpeed : public geometry::ScalarState<AngularSpeed>
    {
    public:
        static AngularSpeed
        radians_per_millisecond(geometry::Scalar radians_per_millisecond)
        {
            return {radians_per_millisecond * constants::radpms2radps};
        }

        static AngularSpeed
        radians_per_second(geometry::Scalar radians_per_second)
        {
            return {radians_per_second};
        }

        std::string
        to_string() const
        {
            return to_radians_per_second().to_string();
        }

        Scalar
        to_radians_per_millisecond() const
        {
            return {_representation * constants::radps2radpms,
                    constants::names::radians_per_millisecond,
                    constants::symbols::radians_per_millisecond};
        }

        Scalar
        to_radians_per_second() const
        {
            return {_representation,
                    constants::names::radians_per_millisecond,
                    constants::symbols::radians_per_millisecond};
        }

    protected:
        using geometry::ScalarState<AngularSpeed>::ScalarState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AngularSpeed const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units::angular_speed
