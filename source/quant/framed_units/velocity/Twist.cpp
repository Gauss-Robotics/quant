#include "Twist.h"

#include <quant/framed_geometry/BaseChange.h>
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
        /** TODO: this is not mathematically "correct" but correct in the sense of intuition:
         *        it discards the changes that are induced due to the implicit translation of the
         *        frame the twist is attached to (see the `intuition_about_transformation.ipynb`
         *        or https://hades.mech.northwestern.edu/images/0/0c/MR-tablet-v2.pdf for more
         *        details and the mathematically correct version.
         **/

        return {linear_velocity(twist.linear(), bc),
                                      angular_velocity(twist.angular(), bc)};
    }

}  // namespace quant::framed_units::velocity