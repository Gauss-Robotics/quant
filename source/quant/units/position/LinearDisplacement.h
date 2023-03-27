#pragma once

#include <quant/geometry/LinearDifference.h>
#include <quant/units/distance/Distance.h>
#include <quant/units/position/Position.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class LinearDisplacement : public geometry::LinearDifference<Domain>

    {

    public:
        using LinearDifference<Domain>::LinearDifference;

        static LinearDisplacement
        milliMeters(double x, double y, double z)
        {
            return LinearDisplacement(Position::milliMeters(x, y, z));
        }

        static LinearDisplacement
        milliMeters(Vector xyz)
        {
            return LinearDisplacement(Position::milliMeters(xyz));
        }

        Vector
        toMilliMeters() const
        {
            return differenceObject_.toMilliMeters();
        }

        Distance
        toDistance() const
        {
            return Distance::MilliMeters(differenceObject_.representation_.norm());
        }
    };

}  // namespace quant::units::position
