#include <quant/framed_units/position/FramedPosition.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/AngularDisplacement.h>


namespace quant::framed_geometry
{
    units::position::Position
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

namespace quant::framed_units::position
{



    void test()
    {
        framed_geometry::BaseChange const transform{
            .from_frame = "from_frame",
            .to_frame = "to_frame"
        };
        framed_units::position::Position const position{};
        auto const result =  transform * position;

    }
}  // namespace quant::framed_units::position