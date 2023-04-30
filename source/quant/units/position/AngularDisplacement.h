#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/Position.h>
#include <quant/units/position_fwd.h>

namespace quant::units::position
{

    class AngularDisplacement : public geometry::Difference<Orientation>
    {

    public:
        static AngularDisplacement
        radians(geometry::AxisAngle const& aa)
        {
            return AngularDisplacement{Orientation::radians(aa)};
        }

        using geometry::Difference<Orientation>::Difference;
    };

}  // namespace quant::units::position
