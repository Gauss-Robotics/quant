#pragma once

#include <quant/geometry/AngularDifference.h>
#include <quant/geometry/AxisAngle.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    class TorqueDifference : public geometry::AngularDifference<Domain>
    {

    public:
        using AngularDifference<Domain>::AngularDifference;

        static TorqueDifference
        newton_meters(AxisAngle const& aa)
        {
            return TorqueDifference{Torque::newton_meters(aa)};
        }

        using StateType = Torque;
    };

}  // namespace quant::units::force
