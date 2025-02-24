#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/Scalar.h>
#include <quant/units/angle/Angle.h>
#include <quant/units/angle/forward_declarations.h>

namespace quant::units::angle
{

    class AngularDifference : public geometry::Difference<Angle>
    {
    public:
        static AngularDifference
        radians(geometry::Scalar radians)
        {
            return AngularDifference{Angle::radians(radians)};
        }

        static AngularDifference
        degrees(geometry::Scalar degrees)
        {
            return AngularDifference{Angle::degrees(degrees)};
        }

        Scalar
        to_radians() const
        {
            return {_difference_object.to_radians(),
                    constants::names::radians,
                    constants::symbols::radians};
        }

        Scalar
        to_degrees() const
        {
            return {_difference_object.to_degrees(),
                    constants::names::degrees,
                    constants::symbols::degrees};
        }

    protected:
        using geometry::Difference<Angle>::Difference;
    };

}  // namespace quant::units::angle
