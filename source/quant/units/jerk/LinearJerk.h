#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/jerk_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::jerk
{

    class LinearJerk : public geometry::LinearState<Domain>
    {
        // Construct.
    public:
        using geometry::LinearState<Domain>::LinearState;
    };

    std::ostream&
    operator<<(std::ostream& out, LinearJerk const& rhs);

}  // namespace quant::units::jerk
