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
        unit_x()
        {
            return {.x = 1};
        }

        static Vector
        unit_y()
        {
            return {.y = 1};
        }

        static Vector
        unit_z()
        {
            return {.z = 1};
        }

        static Vector
        from_eigen(Eigen::Vector3d const& eigen)
        {
            return {.x = eigen.x(), .y = eigen.y(), .z = eigen.z()};
        }

        Eigen::Vector3d
        to_eigen() const
        {
            return {x, y, z};
        }

        std::string
        to_string(std::string const& unit = "") const
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
        return os << "<Vector " << v.to_string() << ">";
    }

}  // namespace quant::geometry
