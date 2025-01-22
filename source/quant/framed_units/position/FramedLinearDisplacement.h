#pragma once

#include <quant/framed_geometry/Framed.h>
#include <quant/units/position/LinearDisplacement.h>
#include <quant/units/position/forward_declarations.h>

namespace quant::framed_units::position
{

    inline units::position::LinearDisplacement
    ld_basis_change(units::position::LinearDisplacement const& ld,
                    framed_geometry::BaseChange const& transform)
    {
        using LDAccessor = geometry::detail::DifferenceAccessor<units::position::LinearDisplacement>;
        using AngularAccessor =
            geometry::detail::DifferenceAccessor<units::position::AngularDisplacement>;
        using LinearAccessor =
            geometry::detail::DifferenceAccessor<units::position::LinearDisplacement>;
        return LDAccessor::make(
            AngularAccessor::representation(transform.transformation.angular()) *
            LDAccessor::representation(ld));
    }

    class LinearDisplacement : public Framed<units::position::LinearDisplacement>
    {
    public:
        using Framed<units::position::LinearDisplacement>::Framed;
    };

    inline std::ostream&
    operator<<(std::ostream& os, framed_units::position::LinearDisplacement const& rhs)
    {
        return os << rhs.to_string();
    }
}  // namespace quant::framed_units::position