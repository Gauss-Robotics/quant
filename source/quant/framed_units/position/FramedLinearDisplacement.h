#pragma once

#include <quant/framed_geometry/FramedDifference.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::framed_units::position
{

    inline LinearDisplacement
    ld_basis_change(LinearDisplacement const& ld,
                    framed_geometry::BaseChange const& transform)
    {
        using LDAccessor = geometry::detail::DifferenceAccessor<LinearDisplacement>;
        using AngularAccessor =
            geometry::detail::DifferenceAccessor<AngularDisplacement>;
        return LDAccessor::make(
            AngularAccessor::representation(transform.transformation.angular()) *
            LDAccessor::representation(ld));
    }

    class LinearDisplacement : public FramedDifference<units::position::LinearDisplacement>
    {
    public:
        using FramedDifference::FramedDifference;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_units::position