#pragma once

#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/jerk_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::jerk
{

    class AngularJerk : public geometry::QuaternionQuantity<Domain>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<Domain>::QuaternionQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularJerk const& rhs);

}  // namespace quant::units::jerk

namespace quant
{
    using units::jerk::AngularJerk;
}  // namespace quant
