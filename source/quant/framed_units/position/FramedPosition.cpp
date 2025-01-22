#include <quant/framed_units/position/FramedPosition.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/LinearDisplacement.h>

namespace quant::framed_units::position
{

    void
    test()
    {
        framed_geometry::BaseChange const transform{.from_frame = "from_frame",
                                                    .to_frame = "to_frame"};
        framed_units::position::Position const position{};
        auto const result = transform * position;
        traits::framed_traits_of<units::position::Position>::basis_change_function(
            position.get_framed_object(), transform);
    }


}  // namespace quant::framed_units::position