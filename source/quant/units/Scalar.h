#pragma once

#include <quant/geometry/Scalar.h>

#include <sstream>
#include <string_view>

namespace quant::units
{

    struct Scalar : public geometry::Scalar
    {

    public:
        Scalar(geometry::Scalar const scalar,
               std::string_view quantity_name,
               std::string_view unit) :
            geometry::Scalar(scalar), quantity_name{quantity_name}, unit{unit}
        {
            ;
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << quantity_name << " " << geometry::Scalar::to_string() << " " << unit;
            return ss.str();
        }

        const std::string_view quantity_name;
        const std::string_view unit;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Scalar const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units
