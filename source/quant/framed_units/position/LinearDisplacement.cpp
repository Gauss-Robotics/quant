#include "LinearDisplacement.h"
#include <quant/framed_geometry/BaseChange.h>
#include <quant/units/position/LinearDisplacement.h>

namespace quant::framed_units::position
{

    quant::LinearDisplacement
    ld_basis_change(quant::LinearDisplacement const& ld,
                    framed_geometry::BaseChange const& transform)
    {
        using LDAccessor =
            geometry::detail::DifferenceAccessor<units::position::LinearDisplacement>;
        using AngularAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        auto const R = AngularAccessor::representation(transform.transformation.angular());
        auto const d = LDAccessor::representation(ld);
        return LDAccessor::make(R.inverse() * d);
    }

    std::ostream&
    operator<<(std::ostream& os, LinearDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_units::position