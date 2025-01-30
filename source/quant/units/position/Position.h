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
        millimeters(geometry::Vector xyz);

        static Position
        meters(geometry::Vector xyz);

        Vector
        to_millimeters() const;

        Vector
        to_meters() const;

        std::string
        to_string() const;

        using LinearState::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Position const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::units::position
