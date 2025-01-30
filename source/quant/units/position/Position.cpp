#include "Position.h"

#include <quant/units/position/Orientation.h>

namespace quant::units::position
{

    Position
    Position::millimeters(geometry::Vector xyz)
    {
        return {xyz};
    }

    Position
    Position::meters(geometry::Vector xyz)
    {
        return {xyz * constants::m2mm};
    }

    Vector
    Position::to_millimeters() const
    {
        return {to_vector(), constants::names::position, constants::symbols::millimeters};
    }

    Vector
    Position::to_meters() const
    {
        return {
            to_vector() * constants::mm2m, constants::names::position, constants::symbols::meters};
    }

    std::string
    Position::to_string() const
    {
        for (auto fn : {&Position::to_meters})
        {
            Vector v = (this->*fn)();
            if (v.x > 1 or v.y > 1 or v.z > 1)
            {
                return v.to_string();
            }
        }

        return to_millimeters().to_string();
    }
}  // namespace quant::units::position

namespace quant::units
{

}  // namespace quant::units
