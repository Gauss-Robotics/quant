#pragma once

#include <quant/geometry/AngularDifference.h>
#include <quant/geometry/AxisAngle.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::units::velocity
{

    class AngularVelocityDifference : public geometry::AngularDifference<Domain>
    {

    public:
        using AngularDifference<Domain>::AngularDifference;
    };

}  // namespace quant::units::velocity
