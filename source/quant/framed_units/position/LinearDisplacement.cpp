#include "LinearDisplacement.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/AngularDisplacement.h>
#include <quant/units/position/LinearDisplacement.h>

#include <ostream>

namespace quant::framed_units::position
{

    units::position::LinearDisplacement
    ld_basis_change(units::position::LinearDisplacement const& ld,
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