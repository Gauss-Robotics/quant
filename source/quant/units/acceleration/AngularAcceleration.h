#pragma once

#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/acceleration_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::acceleration
{

    class AngularAcceleration : public geometry::QuaternionQuantity<Domain>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<Domain>::QuaternionQuantity;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularAcceleration const& rhs);

}  // namespace quant::units::acceleration

namespace quant
{
    using units::acceleration::AngularAcceleration;
}  // namespace quant
