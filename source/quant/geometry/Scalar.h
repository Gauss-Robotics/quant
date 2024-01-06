#pragma once

#include <quant/geometry/forward_declarations.h>

#include <Eigen/Core>

#include <sstream>
#include <string>

namespace quant::geometry
{

    struct Scalar
    {
        double value = 0;

        Scalar(double value) : value{value}
        {
            ;
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << value;
            return ss.str();
        }

        Scalar
        operator*(double rhs) const
        {
            return {value * rhs};
        }

        Scalar
        operator/(double rhs) const
        {
            return {value / rhs};
        }

        operator double() const
        {
            return value;
        }
    };

    inline std::ostream&
    operator<<(std::ostream& os, Scalar const& v)
    {
        return os << v.to_string();
    }

}  // namespace quant::geometry
