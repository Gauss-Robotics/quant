#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/jerk_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::jerk
{

    class AngularJerk : public geometry::AngularState<Domain>
    {
        // Construct.
    public:
        using geometry::AngularState<Domain>::AngularState;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularJerk const& rhs);

}  // namespace quant::units::jerk
