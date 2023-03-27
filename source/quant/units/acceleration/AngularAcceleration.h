#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/acceleration_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class AngularAcceleration : public geometry::AngularState<Domain>
    {
        // Construct.
    public:
        using geometry::AngularState<Domain>::AngularState;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs);

}  // namespace quant::units::acceleration
