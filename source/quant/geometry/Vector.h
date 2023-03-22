#pragma once

#include <Eigen/Core>

#include <sstream>
#include <string>

namespace quant::geometry
{

    /**
     * @brief Euclidian point convenience struct for named parameter semantics.
     */
    struct Vector
    {
        double x = 0;
        double y = 0;
        double z = 0;

        static Vector
        UnitX()
        {
            return {.x = 1};
        }

        static Vector
        UnitY()
        {
            return {.y = 1};
        }

        static Vector
        UnitZ()
        {
            return {.z = 1};
        }

        static Vector
        FromEigen(Eigen::Vector3d const& eigen)
        {
            return {.x = eigen.x(), .y = eigen.y(), .z = eigen.z()};
        }

        Eigen::Vector3d
        toEigen() const
        {
            return {x, y, z};
        }

        std::string
        toString(std::string const& unit = "") const
        {
            // [1.1 2.2 3.3] m/s
            std::stringstream ss;
            ss << "[" << x << " " << y << " " << z << "]";
            if (not unit.empty())
            {
                ss << " " << unit;
            }
            return ss.str();
        }
    };

    inline std::ostream&
    operator<<(std::ostream& os, Vector const& v)
    {
        return os << v.toString();
    }

}  // namespace quant::geometry

namespace quant
{

    using geometry::Vector;

}  // namespace quant
