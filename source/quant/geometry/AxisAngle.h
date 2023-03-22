#pragma once

#include <quant/geometry/Vector.h>

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
        AroundX(double angle)
        {
            return {.angle = angle, .axis = Vector::UnitX()};
        }

        static AxisAngle
        AroundY(double angle)
        {
            return {.angle = angle, .axis = Vector::UnitY()};
        }

        static AxisAngle
        AroundZ(double angle)
        {
            return {.angle = angle, .axis = Vector::UnitZ()};
        }

        static AxisAngle
        FromEigen(Eigen::AngleAxisd const& eigen)
        {
            return {.angle = eigen.angle(), .axis = Vector::FromEigen(eigen.axis())};
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

namespace quant
{

    using geometry::AxisAngle;

}  // namespace quant
