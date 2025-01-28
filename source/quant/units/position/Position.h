#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/position/constants.h>
#include <quant/units/position/forward_declarations.h>

#include <ostream>

namespace quant::units::position
{

    /**
     * @brief Models a position in Euclidean space.
     */
    class Position : public geometry::LinearState<Position>
    {

    public:
        static Position
        millimeters(geometry::Vector xyz)
        {
            return {xyz};
        }

        static Position
        meters(geometry::Vector xyz)
        {
            return {xyz * constants::m2mm};
        }

        Vector
        to_millimeters() const
        {
            return {to_vector(), constants::names::position, constants::symbols::millimeters};
        }

        Vector
        to_meters() const
        {
            return {to_vector() * constants::mm2m,
                    constants::names::position,
                    constants::symbols::meters};
        }

        std::string
        to_string() const
        {
            Vector (Position::*member_function_ptr)();

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

        using LinearState::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Position const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::units::position
