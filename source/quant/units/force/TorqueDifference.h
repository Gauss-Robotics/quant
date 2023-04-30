#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    class TorqueDifference : public geometry::Difference<Torque>
    {

    public:
        static TorqueDifference
        newton_meters(AxisAngle const& aa)
        {
            return TorqueDifference{Torque::newton_meters(aa)};
        }

        using geometry::Difference<Torque>::Difference;
    };

}  // namespace quant::units::force
