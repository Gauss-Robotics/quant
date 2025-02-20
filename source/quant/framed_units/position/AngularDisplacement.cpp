#include "AngularDisplacement.h"

#include <quant/framed_geometry/forward_declarations.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/AngularDisplacement.h>

namespace quant::framed_units::position
{

    quant::AngularDisplacement
    ad_basis_change(quant::AngularDisplacement const& ld, BaseChange const& transform)
    {
        using LDAccessor = geometry::detail::DifferenceAccessor<quant::AngularDisplacement>;
#ifdef QUANT_FRAMED_USE_RIGHT_OPERATIONS
        /** T * r = T * (R2 - R1) == T * R2 - T * R1
         * this is only True for T == I
         *
         * This might look wrong if you look at it from a "global" perspective, but it is correct
         * as we use the right plus and minus operators and therefore the changes are expressed in
         * the local frame of the object. As the objects positions and orientations (in the global
         * coordinate system) do not change under a coordinate transformation (only the coordinate
         * system does and therfore the numerical values), the changes in the local frame are
         * always the same.
         *
         */

        return LDAccessor::make(LDAccessor::representation(ld));
#else
        using TransformAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        auto const R = TransformAccessor::representation(transform.transformation.angular());
        auto const o = LDAccessor::representation(ld);
        return LDAccessor::make(R.inverse() * o * R);
#endif
    }
}  // namespace quant::framed_units::position