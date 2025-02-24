#include "AngularDisplacement.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/AngularDisplacement.h>

#include <string_view>

namespace quant::framed_units::position
{

    quant::AngularDisplacement
    ad_basis_change(quant::AngularDisplacement const& ld, BaseChange const& transform)
    {
        // only true for the convention of expressing differences in the global/base frame
        using ADAccessor = geometry::detail::DifferenceAccessor<quant::AngularDisplacement>;
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        auto const R = TransformAccessor::representation(transform.transformation.angular());
        auto const o = ADAccessor::representation(ld);
        return ADAccessor::make(R.inverse() * o * R);
    }
}  // namespace quant::framed_units::position