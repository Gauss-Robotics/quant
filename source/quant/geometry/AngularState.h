#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry/forward_declarations.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <string>

namespace quant::geometry
{

    template <typename StateType>
    class AngularState
    {

    public:
        // Construct.

        /**
         * @brief Default constructed quaternion.
         */
        AngularState() : _representation(1, 0, 0, 0)
        {
            ;
        }

        static StateType
        zero()
        {
            return StateType();
        }

        // Compare.

        bool
        operator==(StateType const& rhs) const
        {
            // TODO: This holds only for the state NOT for the difference
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return _representation.coeffs() == rhs._representation.coeffs() or
                   _representation.coeffs() == -rhs._representation.coeffs();
        }

        bool
        operator!=(StateType const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            return _representation.coeffs() != rhs._representation.coeffs() and
                   _representation.coeffs() != -rhs._representation.coeffs();
        }

        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.coeffs().isApprox(rhs._representation.coeffs(), tolerance) or
                   _representation.coeffs().isApprox(-rhs._representation.coeffs(), tolerance);
        }

        Eigen::Quaterniond
        operator/(StateType const& rhs) const
        {
            return _representation / rhs._representation;
        }

        using GeometricRepresentationType = Eigen::Quaterniond;

    protected:
        // Construct.

        AngularState(AxisAngle const& aa) : _representation{aa.to_eigen()}
        {
            ;
        }

        AngularState(Eigen::Quaterniond const& quaternion) : _representation{quaternion}
        {
            ;
        }

        // Convert.

        AxisAngle
        to_axis_angle() const
        {
            return AxisAngle::from_eigen(Eigen::AngleAxisd{_representation});
        }

        Eigen::Quaterniond _representation;

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry
