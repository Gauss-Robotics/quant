#include "SpatialDisplacement.h"

namespace quant::units::position
{
    SpatialDisplacement::SpatialDisplacement(LinearDisplacement const& linear,
                                                    AngularDisplacement const& angular) :
        Difference(
            Pose(static_cast<Position const>(linear), static_cast<Orientation const>(angular)))
    {
        ;
    }

    LinearDisplacement
    SpatialDisplacement::linear() const
    {
        return LinearDisplacement(_difference_object.linear());
    }

    AngularDisplacement
    SpatialDisplacement::angular() const
    {
        return AngularDisplacement(_difference_object.angular());
    }

    SpatialDisplacement
    SpatialDisplacement::inverse() const
    {
        return SpatialDisplacement(_difference_object.inverse());
    }
}  // namespace quant::units::position