#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<quant::Orientation>
    {
        using DifferenceType = units::position::AngularDisplacement;
    };

}  // namespace quant::geometry

namespace quant::units::position
{

    class AngularDisplacement : public AngularDifference<Orientation>
    {

    public:
        using AngularDifference<Orientation>::AngularDifference;

        static AngularDisplacement
        Radians(AxisAngle const& aa)
        {
            return AngularDisplacement(Orientation::Radians(aa));
        }
    };

}  // namespace quant::units::position

namespace quant
{

    using units::position::AngularDisplacement;

}  // namespace quant
