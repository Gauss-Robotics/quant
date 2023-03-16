#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <quant/geometry/QuaternionQuantity.h>


namespace quant::units::force
{

    class Torque : public geometry::QuaternionQuantity<Torque>
    {
        // Construct.
    public:
        using geometry::QuaternionQuantity<Torque>::QuaternionQuantity;

        static Torque
        Zero()
        {
            return Origin();
        }

        static Torque
        NewtonMeters(AxisAngle aa)
        {
            return {aa};
        }
    };


    std::ostream& operator<<(std::ostream& out, const Torque& rhs);

} // namespace quant::units::force


namespace quant
{
    using units::force::Torque;
} // namespace quant
