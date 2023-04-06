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

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << geometry::Vector::to_string() << " " << unit_symbol;
            return ss.str();
        }

        const std::string_view quantity_name;
        const std::string_view unit_symbol;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Vector const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units
