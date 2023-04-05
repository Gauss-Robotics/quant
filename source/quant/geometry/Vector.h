#pragma once

#include <quant/geometry_fwd.h>

#include <Eigen/Core>

#include <sstream>
#include <string>

namespace quant::geometry
{

    /**
     * @brief Euclidean point convenience struct for named parameter semantics.
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

        double
        norm() const
        {
            return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
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
        to_string() const
        {
            std::stringstream ss;
            ss << "[" << x << " " << y << " " << z << "]";
            return ss.str();
        }

        Vector
        operator*(double const rhs) const
        {
            return {.x = x * rhs, .y = y * rhs, .z = z * rhs};
        }

        Vector
        operator/(double const rhs) const
        {
            return {.x = x / rhs, .y = y / rhs, .z = z / rhs};
        }
    };

    inline std::ostream&
    operator<<(std::ostream& os, Vector const& v)
    {
        return os << "<Vector " << v.to_string() << ">";
    }

}  // namespace quant::geometry
