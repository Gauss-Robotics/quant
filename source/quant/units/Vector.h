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
               std::string_view unit) :
            geometry::Vector(vector), quantity_name{quantity_name}, unit{unit}
        {
            ;
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << quantity_name << " " << geometry::Vector::to_string() << " " << unit;
            return ss.str();
        }

        const std::string_view quantity_name;
        const std::string_view unit;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Vector const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units
