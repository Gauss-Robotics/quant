#pragma once


#include <ostream>

#include <Eigen/Geometry>

#include <simox/core/geometry/QuaternionQuantity.h>


namespace simox::core::units::force
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

} // namespace simox::core::units::force


namespace simox
{
    using core::units::force::Torque;
} // namespace simox
