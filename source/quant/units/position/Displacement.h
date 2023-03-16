#pragma once


#include <simox/core/geometry/common.h>
#include <simox/core/units/distance/Distance.h>
#include <simox/core/units/position/Position.h>


namespace simox::core::units::position
{

    class Displacement : public Difference<Position>
    {

    public:
        Displacement() : Difference<Position>()
        {
            ;
        }

        explicit Displacement(const Position& t) : Difference<Position>(t)
        {
            ;
        }

        Distance
        toDistance() const
        {
            return Distance::MilliMeters(differenceObject_.representation_.norm());
        }
    };

} // namespace simox::core::units::position


namespace simox
{

    using core::units::position::Displacement;

}
