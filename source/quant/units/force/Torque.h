#pragma once

#include <quant/geometry/QuaternionQuantity.h>
#include <quant/units/force_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Torque : public geometry::QuaternionQuantity<Domain>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<Domain>::QuaternionQuantity;

        static Torque
        NewtonMeters(AxisAngle aa)
        {
            return {aa};
        }
    };

    std::ostream&
    operator<<(std::ostream& out, Torque const& rhs);

}  // namespace quant::units::force

namespace quant
{

    using units::force::Torque;

}  // namespace quant
