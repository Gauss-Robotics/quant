#include "common.h"

std::ostream&
quant::operator<<(std::ostream& os, Vector const& v)
{
    return os << io::toString(v);
}

std::ostream&
quant::operator<<(std::ostream& os, AxisAngle const& aa)
{
    return os << io::toString(aa);
}

namespace quant
{

    std::string
    io::toString(Vector const& v, std::string const& unit)
    {
        // [1.1 2.2 3.3] m/s
        std::stringstream ss;
        ss << "[" << v.x << " " << v.y << " " << v.z << "]";
        if (not unit.empty())
        {
            ss << " " << unit;
        }
        return ss.str();
    }

    std::string
    io::toString(AxisAngle const& aa, std::string const& unit)
    {
        std::stringstream ss;
        ss << aa.angle;
        if (not unit.empty())
        {
            ss << " " << unit;
        }
        ss << " around " << aa.axis;
        return ss.str();
    }

}  // namespace quant
