#pragma once

#include <quant/geometry/SO3TangentState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/angle/constants.h>
#include <quant/units/velocity/constants.h>
#include <quant/units/velocity/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

#include "quant/units/angular_speed/AngularSpeed.h"

namespace quant::units::velocity
{

    class AngularVelocity : public geometry::SO3TangentState<AngularVelocity>
    {
    public:
        static AngularVelocity
        radians_per_second(geometry::AxisAngle const& aa);

        static AngularVelocity
        radians_per_second(geometry::Vector const& vector);

        static AngularVelocity
        degrees_per_second(geometry::AxisAngle const& aa);

        static AngularVelocity
        degrees_per_second(geometry::Vector const& vector);

        // Convert.

        AxisAngle
        to_radians_per_second() const;

        AxisAngle
        to_degrees_per_second() const;

        AngularSpeed
        to_angular_speed() const;

        std::string
        to_string() const;

        using SO3TangentState::SO3TangentState;
    };

    std::ostream&
    operator<<(std::ostream& out, AngularVelocity const& rhs);

}  // namespace quant::units::velocity
