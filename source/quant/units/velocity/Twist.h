#pragma once

#include <quant/geometry/SE3TangentState.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity/forward_declarations.h>

namespace quant::units::velocity
{

    /**
     * @brief Represents a twist, i.e., a screw of linear and angular velocity.
     */
    class Twist : public geometry::SE3TangentState<Twist>
    {
    public:
        using SE3TangentState::SE3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& os, Twist const& rhs);

}  // namespace quant::units::velocity
