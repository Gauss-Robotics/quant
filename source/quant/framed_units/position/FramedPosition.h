#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/Position.h>
#include <quant/units/position/SpatialDisplacement.h>


namespace quant::framed_units::position
{

    class Position : public Framed<units::position::Position>
    {

    public:
        using Framed<units::position::Position>::Framed;
    };


}  // namespace quant::framed_units::position

namespace quant::framed_geometry
{
    inline units::position::Position
    operator*(framed_geometry::BaseChange const& transform, units::position::Position const& rhs)
    {
        return geometry::detail::StateAccessor<units::position::Position>::make(
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>::representation(
                transform.transformation.angular()) *
                geometry::detail::StateAccessor<units::position::Position>::representation(rhs) +
            geometry::detail::DifferenceAccessor<units::position::LinearDisplacement>::representation(
                transform.transformation.linear()));
    }
}
