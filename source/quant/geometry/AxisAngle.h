#pragma once

#include <quant/geometry/Vector.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Geometry>

#include <sstream>
#include <string>

namespace quant::geometry
{

    /**
     * @brief Angle around axis convenience struct for named parameter semantics.
     */
    struct AxisAngle
    {
        Vector axis{.x = 1, .y = 0, .z = 0};
        double angle = 0;

        static AxisAngle
        around_x(double angle)
        {
            return {.axis = Vector::unit_x(), .angle = angle};
        }

        static AxisAngle
        around_y(double angle)
        {
            return {.axis = Vector::unit_y(), .angle = angle};
        }

        static AxisAngle
        around_z(double angle)
        {
            return {.axis = Vector::unit_z(), .angle = angle};
        }

        static AxisAngle
        from_eigen(Eigen::AngleAxisd const& eigen)
        {
            return {.axis = Vector::from_eigen(eigen.axis()), .angle = eigen.angle()};
        }

        static AxisAngle
        from_eigen(Eigen::Ref<Eigen::Matrix3d> eigen)
        {
            return from_eigen(Eigen::AngleAxisd(eigen));
        }

        Eigen::AngleAxisd
        to_eigen() const
        {
            return {angle, axis.to_eigen()};
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << angle << " around axis " << axis.to_string();
            return ss.str();
        }
    };

    inline std::ostream&
    operator<<(std::ostream& os, AxisAngle const& aa)
    {
        return os << aa.to_string();
    }

}  // namespace quant::geometry
