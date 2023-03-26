#pragma once

#include <quant/geometry/VectorQuantity.h>
#include <quant/units/acceleration_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class LinearAcceleration : public geometry::VectorQuantity<Domain>
    {
        // Construct.
    public:
        using geometry::VectorQuantity<Domain>::VectorQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, LinearAcceleration const& rhs);

}  // namespace quant::units::acceleration
