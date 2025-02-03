#include "Wrench.h"

#include <quant/framed_geometry/Adjoint.h>
#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Vector.h>
#include <quant/units/force/Force.h>
#include <quant/units/force/Torque.h>

#include "forward_declarations.h"

namespace quant::framed_units::force
{

    Torque
    Wrench::angular() const
    {
        return {get_framed_object().angular(),
                {.name = get_name(), .base_frame = get_base_frame()}};
    }

    Force
    Wrench::linear() const
    {
        return {get_framed_object().linear(), {.name = get_name(), .base_frame = get_base_frame()}};
    }

    std::ostream&
    operator<<(std::ostream& out, Wrench const& rhs)
    {
        return out << rhs.to_string();
    }

    units::force::Wrench
    base_change::wrench(units::force::Wrench const& wrench,
                        framed_geometry::BaseChange const& base_change)
    {
        // Formula 3.98 from Modern Robotics
        // se3 = [m, f]
        Eigen::Vector<double, 6> se3 = Eigen::Vector<double, 6>::Zero();
        se3.head<3>() = wrench.angular().to_newton_meters().to_eigen().axis() *
                        wrench.angular().to_newton_meters().to_eigen().angle();
        se3.tail<3>() = wrench.linear().to_newtons().to_eigen();
        framed_geometry::Adjoint const adjoint{base_change.transformation};
        Eigen::Vector<double, 6> se3_prime = adjoint.matrix().transpose() * se3;
        return units::force::Wrench{
            units::force::Force::newtons(
                geometry::Vector{se3_prime(3, 0), se3_prime(4, 0), se3_prime(5, 0)}),
            units::force::Torque::newton_meters(geometry::AxisAngle::from_eigen(
                Eigen::AngleAxisd(se3_prime.head<3>().norm(), se3_prime.head<3>().normalized())))};
    }
}  // namespace quant::framed_units::force