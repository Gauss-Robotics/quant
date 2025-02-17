#include "Twist.h"

#include <quant/framed_geometry/Adjoint.h>
#include <quant/framed_geometry/BaseChange.h>
#include <quant/geometry/detail/DifferenceAccessor.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/units/position/SpatialDisplacement.h>
#include <quant/units/velocity/AngularVelocity.h>
#include <quant/units/velocity/LinearVelocity.h>
#include <quant/units/velocity/Twist.h>

#include <cassert>

#include "forward_declarations.h"

namespace quant::framed_units::velocity
{
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
        auto const adjoint = framed_geometry::Adjoint(bc.transformation.inverse());
        auto const V =
            geometry::detail::StateAccessor<units::velocity::Twist>::representation(twist);
        // Equation 3.76ff Modern Robotics
        return geometry::detail::StateAccessor<units::velocity::Twist>::make(adjoint * V);
    }

}  // namespace quant::framed_units::velocity