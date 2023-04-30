#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::units::velocity
{

    class AngularVelocityDifference : public geometry::Difference<AngularVelocity>
    {

    public:
        using geometry::Difference<AngularVelocity>::Difference;
    };

}  // namespace quant::units::velocity
