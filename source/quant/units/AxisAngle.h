#pragma once

#include <quant/geometry/AxisAngle.h>

#include <sstream>
#include <string_view>

namespace quant::units
{

    struct AxisAngle : public geometry::AxisAngle
    {

    public:
        AxisAngle(geometry::AxisAngle const axis_angle,
                  std::string_view quantity_name,
                  std::string_view unit_symbol) :
            geometry::AxisAngle(axis_angle), quantity_name{quantity_name}, unit_symbol{unit_symbol}
        {
            ;
        }

        AxisAngle(AxisAngle const axis_angle,
                  std::string_view quantity_name,
                  std::string_view unit_symbol) :
            geometry::AxisAngle(axis_angle), quantity_name{quantity_name}, unit_symbol{unit_symbol}
        {
            ;
        }

        std::string
        to_string() const
        {
            std::stringstream ss;
            ss << angle << " " << unit_symbol << " around axis " << axis.to_string();
            return ss.str();
        }

        const std::string_view quantity_name;
        const std::string_view unit_symbol;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AxisAngle const& rhs)
    {
        return out << rhs.to_string();
    }

}  // namespace quant::units
