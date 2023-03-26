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
        radians(AxisAngle const& aa)
        {
            return AngularDisplacement(Orientation::radians(aa));
        }
    };

}  // namespace quant::units::position
