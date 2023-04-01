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
        milli_meters(double x, double y, double z)
        {
            return LinearDisplacement{Position::milli_meters(x, y, z)};
        }

        static LinearDisplacement
        milli_meters(Vector xyz)
        {
            return LinearDisplacement{Position::milli_meters(xyz)};
        }

        Vector
        to_milli_meters() const
        {
            return difference_object_.to_milli_meters();
        }

        Distance
        to_distance() const
        {
            return Distance::MilliMeters(difference_object_.to_milli_meters().to_eigen().norm());
        }

        using StateType = Position;
    };

}  // namespace quant::units::position
