#include "SpatialDisplacement.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_units/position/AngularDisplacement.h>
#include <quant/framed_units/position/LinearDisplacement.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/SpatialDisplacement.h>
#include <quant/units/position/forward_declarations.h>


#include "forward_declarations.h"

namespace quant::framed_units::position
{

    units::position::SpatialDisplacement
    sd_basis_change(units::position::SpatialDisplacement const& sd,
                    framed_geometry::BaseChange const& transform)
    {
        // only true for the convention of expressing differences in the global/base frame
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;

        auto const T = TransformAccessor::representation(transform.transformation);
        auto const S = TransformAccessor::representation(sd);
        return TransformAccessor::make(T.inverse() * S * T);
    }

    LinearDisplacement
    SpatialDisplacement::linear() const
    {
        return {get_framed_object().linear(), get_base_frame()};
    }

    AngularDisplacement
    SpatialDisplacement::angular() const
    {
        return {get_framed_object().angular(), get_base_frame()};
    }
}  // namespace quant::framed_units::position