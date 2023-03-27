#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/acceleration_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAcceleration : public geometry::LinearState<Domain>
    {
        // Construct.
    public:
        using geometry::LinearState<Domain>::LinearState;
    };

    std::ostream&
    operator<<(std::ostream& out, LinearAcceleration const& rhs);

}  // namespace quant::units::acceleration
