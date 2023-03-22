#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/Difference.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/Orientation.h>
#include <quant/units/position_fwd.h>

namespace quant::geometry
{

    template <>
    struct DefineDifferenceType<quant::Orientation>
    {
        using DifferenceType = units::position::AngularDisplacement;
    };

}  // namespace quant::geometry

namespace quant::units::position
{

    class AngularDisplacement : public Difference<Orientation>
    {

    public:
        AngularDisplacement() : Difference<Orientation>()
        {
            ;
        }

        explicit AngularDisplacement(Orientation const& t) : Difference<Orientation>(t)
        {
            ;
        }

        static AngularDisplacement
        Radians(AxisAngle const& aa)
        {
            return AngularDisplacement(Orientation::Radians(aa));
        }

        Position
        operator*(Position const& position) const
        {
            return Position{differenceObject_.representation_ * position.representation_};
        }

        LinearDisplacement
        operator*(LinearDisplacement const& linearDisplacement) const
        {
            return LinearDisplacement(
                Position{differenceObject_.representation_ *
                         linearDisplacement.differenceObject_.representation_});
        }
    };

}  // namespace quant::units::position

namespace quant
{

    using units::position::SpatialDisplacement;

}  // namespace quant
