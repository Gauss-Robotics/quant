#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/position_constants.h>
#include <quant/units/position_fwd.h>

#include <ostream>

namespace quant::units::position
{

    /**
     * @brief Models a position in Euclidean space.
     */
    class Position : public geometry::LinearState<Domain>
    {

    public:
        static Position
        millimeters(geometry::Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }

        static Position
        meters(geometry::Vector xyz)
        {
            return {xyz.x * constants::m2mm, xyz.y * constants::m2mm, xyz.z * constants::m2mm};
        }

        Vector
        to_millimeters() const
        {
            return {to_vector(), constants::position_name, constants::meters};
        }

        Vector
        to_meters() const
        {
            return {to_vector() * constants::mm2m, constants::position_name, constants::meters};
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, Position const& rhs)
    {
        return os << rhs.to_millimeters();
    }

}  // namespace quant::units::position
