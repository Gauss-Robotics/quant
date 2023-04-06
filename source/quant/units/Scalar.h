#pragma once

#include <quant/geometry/Scalar.h>

#include <sstream>
#include <string_view>

namespace quant::units
{

    struct Scalar : public geometry::Scalar
    {

    public:
        Scalar(geometry::Scalar scalar,
               std::string_view quantity_name,
               std::string_view unit_symbol) :
            geometry::Scalar(scalar), quantity_name{quantity_name}, unit_symbol{unit_symbol}
        {
            ;
        }

        Scalar(Scalar scalar, std::string_view quantity_name, std::string_view unit_symbol) :
            geometry::Scalar(scalar), quantity_name{quantity_name}, unit_symbol{unit_symbol}
        {
            ;
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << geometry::Scalar::to_string() << " " << unit_symbol;
            return ss.str();
        }

        const std::string_view quantity_name;
        const std::string_view unit_symbol;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Scalar const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units
