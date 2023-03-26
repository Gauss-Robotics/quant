#pragma once

#include <quant/geometry/Spatial.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity_fwd.h>

namespace quant::units::velocity
{

    /**
     * @brief Represents a twist, i.e., a screw of linear and angular velocity.
     */
    class Twist : public Spatial<Domain>
    {
        // Construct.
    public:
        using Spatial<Domain>::Spatial;
    };

}  // namespace quant::units::velocity
