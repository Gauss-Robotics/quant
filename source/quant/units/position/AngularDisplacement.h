#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class AngularDisplacement : public AngularDifference<Domain>
    {

    public:
        using AngularDifference<Domain>::AngularDifference;

        static AngularDisplacement
        Radians(AxisAngle const& aa)
        {
            return AngularDisplacement(Orientation::Radians(aa));
        }
    };

}  // namespace quant::units::position
