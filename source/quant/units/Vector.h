#pragma once

#include <quant/geometry/Vector.h>

#include <sstream>
#include <string_view>

namespace quant::units
{

    struct Vector : public geometry::Vector
    {

    public:
        Vector(geometry::Vector const vector,
               std::string_view quantity_name,
               std::string_view unit_symbol) :
            geometry::Vector(vector), quantity_name{quantity_name}, unit_symbol{unit_symbol}
        {
            ;
        }

        Vector(Vector const vector, std::string_view quantity_name, std::string_view unit_symbol) :
            geometry::Vector(vector), quantity_name{quantity_name}, unit_symbol{unit_symbol}
        {
            ;
        }

        Vector(Eigen::Vector3d const vector,
               std::string_view quantity_name,
               std::string_view unit_symbol) :
            geometry::Vector(geometry::Vector::from_eigen(vector)),
            quantity_name{quantity_name},
            unit_symbol{unit_symbol}
        {
            ;
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << geometry::Vector::to_string() << " " << unit_symbol;
            return ss.str();
        }

        static Vector
        unit_x(std::string_view const& quantity_name, std::string_view const& unit_symbol)
        {
            return {geometry::Vector::unit_x(), quantity_name, unit_symbol};
        }

        static Vector
        unit_y(std::string_view const& quantity_name, std::string_view const& unit_symbol)
        {
            return {geometry::Vector::unit_y(), quantity_name, unit_symbol};
        }

        static Vector
        unit_z(std::string_view const& quantity_name, std::string_view const& unit_symbol)
        {
            return {geometry::Vector::unit_z(), quantity_name, unit_symbol};
        }

        Vector
        operator*(double const rhs) const
        {
            return {geometry::Vector::operator*(rhs), quantity_name, unit_symbol};
        }

        Vector
        operator/(double const rhs) const
        {
            return {geometry::Vector::operator/(rhs), quantity_name, unit_symbol};
        }

        std::string_view const quantity_name;
        std::string_view const unit_symbol;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Vector const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units
