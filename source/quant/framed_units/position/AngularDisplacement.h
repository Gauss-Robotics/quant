#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::framed_units::position
{

    inline AngularDisplacement
    ad_basis_change(AngularDisplacement const& ld, BaseChange const& /*transform*/)
    {
        using LDAccessor = geometry::detail::DifferenceAccessor<AngularDisplacement>;
        // T * r = T * (R2 - R1) == T * R2 - T * R1
        // this is only True for T == I
        return LDAccessor::make(LDAccessor::representation(ld));
    }

    class AngularDisplacement : public FramedDifference<units::position::AngularDisplacement>
    {
    public:
        using Difference::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, AngularDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_units::position