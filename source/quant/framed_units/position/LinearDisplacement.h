#pragma once

#include <quant/framed_geometry/Difference.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::framed_units::position
{

    inline LinearDisplacement
    ld_basis_change(LinearDisplacement const& ld, framed_geometry::BaseChange const& transform)
    {
        using LDAccessor = geometry::detail::DifferenceAccessor<LinearDisplacement>;
        using AngularAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        auto const R = AngularAccessor::representation(transform.transformation.angular());
        auto const d = LDAccessor::representation(ld);
        return LDAccessor::make(R.inverse() * d);
    }

    class LinearDisplacement : public FramedDifference<units::position::LinearDisplacement>
    {
    public:
        using Difference::Difference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_units::position