#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/framed_units/position/forward_declarations.h>
#include <quant/units/position/SpatialDisplacement.h>

namespace quant::framed_units::position
{
    inline units::position::SpatialDisplacement
    sd_basis_change(units::position::SpatialDisplacement const& sd,
                    framed_geometry::BaseChange const& transform)
    {
        // Corresponds to the left + operator and is NOT the same as sd + transform, because here
        // the transform is in the "global" or base frame
        using TransformAccessor = geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        return TransformAccessor::make(
            TransformAccessor::representation(transform.transformation) *
            TransformAccessor::representation(sd));
    }

    class SpatialDisplacement : public Framed<units::position::SpatialDisplacement>
    {
    public:
        using Framed<units::position::SpatialDisplacement>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::position::SpatialDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }

}  // namespace quant::framed_units::position
