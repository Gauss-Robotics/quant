#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/force/Torque.h>
#include <quant/units/force/forward_declarations.h>

namespace quant::units::force
{

    class TorqueDifference : public geometry::Difference<Torque>
    {

    public:
        static TorqueDifference
        newton_meters(geometry::AxisAngle const& aa);

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& out, TorqueDifference const& rhs);

}  // namespace quant::units::force
