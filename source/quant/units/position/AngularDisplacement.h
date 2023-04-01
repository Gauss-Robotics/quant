#pragma once

#include <quant/geometry/AngularDifference.h>
#include <quant/geometry/AxisAngle.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/Position.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class AngularDisplacement : public geometry::AngularDifference<Domain>
    {

    public:
        static AngularDisplacement
        radians(AxisAngle const& aa)
        {
            return AngularDisplacement{Orientation::radians(aa)};
        }

        using geometry::AngularDifference<Domain>::AngularDifference;
    };

}  // namespace quant::units::position
