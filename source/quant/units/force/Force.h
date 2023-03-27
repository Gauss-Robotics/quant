#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/force_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Force : public geometry::LinearState<Domain>
    {
        // Construct.
    public:
        using geometry::LinearState<Domain>::LinearState;

        static Force
        newton(Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }
    };

    std::ostream&
    operator<<(std::ostream& out, Force const& rhs);

}  // namespace quant::units::force
