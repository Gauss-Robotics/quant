#include "SpeedDifference.h"

#include <quant/units/velocity/LinearVelocityDifference.h>

namespace quant::units::speed
{

    SpeedDifference::SpeedDifference(LinearVelocityDifference const& vel) :
        SpeedDifference::SpeedDifference(vel.to_speed_difference())
    {
        ;
    }

    SpeedDifference
    SpeedDifference::millimeters_per_second(geometry::Scalar millimeters_per_second)
    {
        return SpeedDifference{Speed::millimeters_per_second(millimeters_per_second)};
    }

    SpeedDifference
    SpeedDifference::meters_per_second(geometry::Scalar meters_per_second)
    {
        return SpeedDifference{Speed::meters_per_second(meters_per_second)};
    }

    Scalar
    SpeedDifference::to_millimeters_per_second() const
    {
        return _difference_object.to_millimeters_per_second();
    }

    Scalar
    SpeedDifference::to_meters_per_second() const
    {
        return _difference_object.to_meters_per_second();
    }
}  // namespace quant::units::speed
