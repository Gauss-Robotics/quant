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
        aroundX(double angle)
        {
            return {.angle = angle, .axis = Vector::unitX()};
        }

        static AxisAngle
        aroundY(double angle)
        {
            return {.angle = angle, .axis = Vector::unitY()};
        }

        static AxisAngle
        aroundZ(double angle)
        {
            return {.angle = angle, .axis = Vector::unitZ()};
        }

        static AxisAngle
        fromEigen(Eigen::AngleAxisd const& eigen)
        {
            return {.angle = eigen.angle(), .axis = Vector::fromEigen(eigen.axis())};
        }

        Eigen::AngleAxisd
        toEigen() const
        {
            return {angle, axis.toEigen()};
        }

        std::string
        toString(std::string const& unit = "") const
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
        return os << aa.toString();
    }

}  // namespace quant::geometry
