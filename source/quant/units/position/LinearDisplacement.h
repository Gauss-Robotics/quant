#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/distance/Distance.h>
#include <quant/units/position/Position.h>
#include <quant/units/position_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<Position>
    {
        using DifferenceType = units::position::LinearDisplacement;
    };

}  // namespace quant::geometry

namespace quant::units::position
{

    class LinearDisplacement : public Difference<Position>
    {

    public:
        LinearDisplacement() : Difference<Position>()
        {
            ;
        }

        explicit LinearDisplacement(Position const& t) : Difference<Position>(t)
        {
            ;
        }

        static LinearDisplacement
        MilliMeters(double x, double y, double z)
        {
            return LinearDisplacement(Position::MilliMeters(x, y, z));
        }

        static LinearDisplacement
        MilliMeters(Vector xyz)
        {
            return LinearDisplacement(Position::MilliMeters(xyz));
        }

        Vector
        toMilliMeters() const
        {
            return differenceObject_.toMilliMeters();
        }

        Distance
        toDistance() const
        {
            return Distance::MilliMeters(differenceObject_.representation_.norm());
        }
    };

}  // namespace quant::units::position

namespace quant
{

    using units::position::LinearDisplacement;

}
