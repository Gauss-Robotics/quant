#pragma once

#include <quant/geometry/SO3TangentState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/force/constants.h>
#include <quant/units/force/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::force
{

    class Torque : public geometry::SO3TangentState<Torque>
    {
        // Construct.
    public:
        static Torque
        newton_meters(geometry::AxisAngle aa);

        static Torque
        newton_meters(geometry::Vector vector);

        AxisAngle
        to_newton_meters() const;

        std::string
        to_string() const;

        using SO3TangentState::SO3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& out, Torque const& rhs);

}  // namespace quant::units::force
