#pragma once

#include <quant/geometry/LinearState.h>
#include <quant/units/Vector.h>
#include <quant/units/jerk_constants.h>
#include <quant/units/jerk_fwd.h>

#include <Eigen/Geometry>

#include <ostream>

namespace quant::units::jerk
{

    class LinearJerk : public geometry::LinearState<Domain>
    {
    public:
        static LinearJerk
        millimeters_per_second_cubed(geometry::Vector xyz)
        {
            return {xyz};
        }

        Vector
        to_millimeters_per_second_cubed() const
        {
            return {to_vector(),
                    constants::names::linear_jerk,
                    constants::symbols::millimeters_per_second_cubed};
        }

        using geometry::LinearState<Domain>::LinearState;
    };

    inline std::ostream&
    operator<<(std::ostream& os, LinearJerk const& rhs)
    {
        return os << rhs.to_millimeters_per_second_cubed();
    }

}  // namespace quant::units::jerk
