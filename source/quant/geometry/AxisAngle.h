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
        double angle = 0;
        Vector axis{.x = 1, .y = 0, .z = 0};

        static AxisAngle
        around_x(double angle)
        {
            return {.angle = angle, .axis = Vector::unit_x()};
        }

        static AxisAngle
        around_y(double angle)
        {
            return {.angle = angle, .axis = Vector::unit_y()};
        }

        static AxisAngle
        around_z(double angle)
        {
            return {.angle = angle, .axis = Vector::unit_z()};
        }

        static AxisAngle
        from_eigen(Eigen::AngleAxisd const& eigen)
        {
            return {.angle = eigen.angle(), .axis = Vector::from_eigen(eigen.axis())};
        }

        Eigen::AngleAxisd
        to_eigen() const
        {
            return {angle, axis.to_eigen()};
        }

        std::string
        to_string(std::string const& unit = "") const
        {
            std::stringstream ss;
            ss << angle;
            if (not unit.empty())
            {
                ss << " " << unit;
            }
            ss << " around " << axis;
            return ss.str();
        }
    };

    inline std::ostream&
    operator<<(std::ostream& os, AxisAngle const& aa)
    {
        return os << aa.to_string();
    }

}  // namespace quant::geometry
