#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/forward_declarations.h>

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

        static AngularDisplacement
        degrees(geometry::AxisAngle const& aa)
        {
            return AngularDisplacement{Orientation::degrees(aa)};
        }

        static AngularDisplacement
        radians(Eigen::Quaterniond const& q)
        {
            return AngularDisplacement{Orientation::radians(q)};
        }

        static AngularDisplacement
        degrees(Eigen::Quaterniond const& q)
        {
            return AngularDisplacement{Orientation::degrees(q)};
        }

        using geometry::Difference<Orientation>::Difference;
    };

}  // namespace quant::units::position
