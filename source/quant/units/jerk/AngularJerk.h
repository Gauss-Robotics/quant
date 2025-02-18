#pragma once

#include <quant/geometry/AngularState.h>
#include <quant/units/AxisAngle.h>
#include <quant/units/jerk/constants.h>
#include <quant/units/jerk/forward_declarations.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::jerk
{

    class AngularJerk : public geometry::AngularState<AngularJerk>
    {
    public:
        static AngularJerk
        radians_per_second_cubed(geometry::AxisAngle aa)
        {
            return {aa};
        }

        AxisAngle
        to_radians_per_second_cubed() const
        {
            return {to_axis_angle(),
                    constants::names::angular_jerk,
                    constants::symbols::radians_per_second_cubed};
        }

        using AngularState::AngularState;
    };

    inline std::ostream&
    operator<<(std::ostream& out, AngularJerk const& rhs)
    {
        return out << rhs.to_radians_per_second_cubed();
    }

}  // namespace quant::units::jerk
