#pragma once

#include <quant/geometry/VectorQuantity.h>
#include <quant/units/jerk_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::jerk
{

    class LinearJerk : public geometry::VectorQuantity<Domain>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<Domain>::VectorQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, LinearJerk const& rhs);

}  // namespace quant::units::jerk
