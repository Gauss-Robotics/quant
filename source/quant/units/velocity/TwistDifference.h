#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/velocity/AngularVelocityDifference.h>
#include <quant/units/velocity/LinearVelocityDifference.h>
#include <quant/units/velocity/Twist.h>
#include <quant/units/velocity/forward_declarations.h>

namespace quant::units::velocity
{

    /**
     * @brief Represents a twist, i.e., a screw of linear and angular velocity.
     */
    class TwistDifference : public geometry::Difference<Twist>
    {
    public:
        TwistDifference(LinearVelocityDifference const& linear,
                        AngularVelocityDifference const& angular);

        LinearVelocityDifference
        linear() const;

        AngularVelocityDifference
        angular() const;

        using Difference::Difference;
    };

    std::ostream&
    operator<<(std::ostream& os, TwistDifference const& rhs);

}  // namespace quant::units::velocity
