#include "common.h"


std::ostream&
simox::operator<<(std::ostream& os, const Vector& v)
{
    return os << io::toString(v);
}


std::ostream&
simox::operator<<(std::ostream& os, const AxisAngle& aa)
{
    return os << io::toString(aa);
}


namespace simox
{

    std::string
    io::toString(const Vector& v, const std::string& unit)
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
    io::toString(const AxisAngle& aa, const std::string& unit)
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

} // namespace simox
