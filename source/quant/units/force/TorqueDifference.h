#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force_fwd.h>

namespace quant::units::force
{

    class TorqueDifference : public AngularDifference<Domain>
    {

    public:
        using AngularDifference<Domain>::AngularDifference;

        static TorqueDifference
        NewtonMeters(AxisAngle const& aa)
        {
            return TorqueDifference{Torque::NewtonMeters(aa)};
        }
    };

}  // namespace quant::units::force
