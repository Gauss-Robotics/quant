#include "Twist.h"

#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/units/position/SpatialDisplacement.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity/Twist.h>

#include "forward_declarations.h"

namespace quant::framed_units::velocity
{
    std::ostream&
    operator<<(std::ostream& out, Twist const& rhs)
    {
        return out << rhs.to_string();
    }

    units::velocity::Twist
    base_change::twist(units::velocity::Twist const& twist, framed_geometry::BaseChange const& bc)
    {
        /** NOTE: this is the mathematically "correct" version, but incorrect in the sense of
         *        intuition:
         *        it includes the changes that are induced due to the implicit translation of the
         *        frame the twist is attached to (see the `intuition_about_transformation.ipynb`
         *        or https://hades.mech.northwestern.edu/images/0/0c/MR-tablet-v2.pdf for more
         *        details and the version that adheres to intuition.
         *        The intuitionally correct version would be:
        *         return {linear_velocity(twist.linear(), bc),
                                      angular_velocity(twist.angular(), bc)};
         **/
        using SD = geometry::detail::DifferenceAccessor<units::position::SpatialDisplacement>;
        using AV = geometry::detail::StateAccessor<units::velocity::AngularVelocity>;
        using LV = geometry::detail::StateAccessor<units::velocity::LinearVelocity>;
        auto const T = SD::representation(bc.transformation).inverse();
        auto const R = T.rotation();
        auto const p = T.translation();
        auto const omega = AV::representation(twist.angular());
        auto const v = LV::representation(twist.linear());
        // Equation 3.76ff Modern Robotics
        return {LV::make(-R * omega * R.transpose() * p + R * v),
                AV::make(static_cast<Eigen::AngleAxisd>(R * omega * R.transpose()))};
    }

}  // namespace quant::framed_units::velocity