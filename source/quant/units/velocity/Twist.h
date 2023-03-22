#pragma once

#include <quant/geometry/Spatial.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/LinearVelocity.h>

namespace quant::units::velocity
{

    /**
     * @brief Represents a twist, i.e., a screw of linear and angular velocity.
     */
    class Twist : public Spatial<LinearVelocity, AngularVelocity, Twist>
    {
        // Construct.
    public:
        using Spatial<LinearVelocity, AngularVelocity, Twist>::Spatial;
    };

}  // namespace quant::units::velocity

namespace quant
{
    using units::velocity::Twist;
}
