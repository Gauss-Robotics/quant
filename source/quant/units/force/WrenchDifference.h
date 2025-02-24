#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/force/Wrench.h>

namespace quant::units::force
{

    class WrenchDifference : public geometry::Difference<Wrench>
    {

    public:
        WrenchDifference(ForceDifference const& force, TorqueDifference const& torque);
        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& out, WrenchDifference const& rhs);

}  // namespace quant::units::force
