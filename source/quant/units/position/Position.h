#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/position_fwd.h>
#include <quant/units/time/Duration.h>

#include <ostream>

namespace quant::units::position
{

    /**
     * @brief Models a position in Euclidean space.
     */
    class Position : public geometry::LinearState<Domain>
    {

    public:
        // Construct.

        using geometry::LinearState<Domain>::LinearState;

        static Position
        milliMeters(double x, double y, double z)
        {
            return {x, y, z};
        }

        static Position
        milliMeters(Vector xyz)
        {
            return {xyz.x, xyz.y, xyz.z};
        }

        static Position
        meters(double x, double y, double z)
        {
            constexpr int m2mm = 1'000;
            return {x * m2mm, y * m2mm, z * m2mm};
        }

        static Position
        meters(Vector xyz)
        {
            constexpr int m2mm = 1'000;
            return {xyz.x * m2mm, xyz.y * m2mm, xyz.z * m2mm};
        }

        // Convert.

        Vector
        toMilliMeters() const
        {
            return {.x = representation_.x(), .y = representation_.y(), .z = representation_.z()};
        }

        using DifferenceType = LinearDisplacement;
    };

    inline std::ostream&
    operator<<(std::ostream& out, Position const& rhs)
    {
        return out << rhs.toString("Position", "mm");
    }

}  // namespace quant::units::position
