#pragma once

#include <quant/geometry/SpatialState.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity/forward_declarations.h>

namespace quant::units::velocity
{

    /**
     * @brief Represents a twist, i.e., a screw of linear and angular velocity.
     */
    class Twist : public geometry::SpatialState<Twist>
    {
    public:
        using geometry::SpatialState<Twist>::SpatialState;
    };

}  // namespace quant::units::velocity
