#include "SpatialAcceleration.h"

#include <quant/framed_units/acceleration/LinearAcceleration.h>
#include <quant/units/acceleration/AngularAcceleration.h>
#include <quant/units/acceleration/LinearAcceleration.h>

#include "forward_declarations.h"
#include "quant/framed_geometry/Adjoint.h"

namespace quant::framed_units::acceleration
{

    AngularAcceleration
    SpatialAcceleration::angular() const
    {
        return AngularAcceleration{get_framed_object().angular(),
                                   {.name = get_name(), .base_frame = get_base_frame()}};
    }

    LinearAcceleration
    SpatialAcceleration::linear() const
    {
        return LinearAcceleration{get_framed_object().linear(),
                                  {.name = get_name(), .base_frame = get_base_frame()}};
    }

    std::ostream&
    operator<<(std::ostream& out, SpatialAcceleration const& rhs)
    {
        return out << rhs.to_string();
    }

    units::acceleration::SpatialAcceleration
    base_change::spatial_acceleration(
        units::acceleration::SpatialAcceleration const& spatial_acceleration,
        framed_geometry::BaseChange const& base_change)
    {
        // Formula 3.98 from Modern Robotics
        // se3 = [m, f]
        Eigen::Vector<double, 6> se3 = Eigen::Vector<double, 6>::Zero();
        se3.head<3>() =
            spatial_acceleration.angular().to_radians_per_second_squared().to_eigen().axis() *
            spatial_acceleration.angular().to_radians_per_second_squared().to_eigen().angle();
        se3.tail<3>() = spatial_acceleration.linear().to_millimeters_per_second_squared().to_eigen();
        framed_geometry::Adjoint const adjoint{base_change.transformation};
        Eigen::Vector<double, 6> se3_prime = adjoint.matrix().transpose() * se3;
        return units::acceleration::SpatialAcceleration{
            units::acceleration::LinearAcceleration::millimeters_per_second_squared(
                geometry::Vector{se3_prime(3, 0), se3_prime(4, 0), se3_prime(5, 0)}),
            units::acceleration::AngularAcceleration::radians_per_second_squared(
                geometry::AxisAngle::from_eigen(Eigen::AngleAxisd(
                    se3_prime.head<3>().norm(), se3_prime.head<3>().normalized())))
        };
    }
}  // namespace quant::framed_units::acceleration