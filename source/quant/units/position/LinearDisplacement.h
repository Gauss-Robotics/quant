#pragma once

#include <quant/geometry/Difference.h>
#include <quant/units/distance/Distance.h>
#include <quant/units/position/Position.h>

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
