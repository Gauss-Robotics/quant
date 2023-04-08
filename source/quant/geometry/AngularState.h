#pragma once

#include <quant/geometry/AxisAngle.h>
#include <quant/geometry/constants.h>
#include <quant/geometry/detail/QuantityAccessor.h>
#include <quant/geometry_fwd.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <string>

namespace quant::geometry
{

    template <typename Domain>
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

        static typename Domain::AngularState
        zero()
        {
            return typename Domain::AngularState();
        }

        // Compare.

        bool
        operator==(typename Domain::AngularState const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return _representation.coeffs() == rhs._representation.coeffs();
        }

        bool
        operator!=(typename Domain::AngularState const& rhs) const
        {
            // TODO(dreher): Eigen >= 3.4
            // return _representation == rhs._representation;
            return _representation.coeffs() != rhs._representation.coeffs();
        }

        bool
        is_approx(typename Domain::AngularState const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        using GeometricRepresentationType = Eigen::Quaterniond const&;
        using GeometricType = traits::StateType;

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

        friend class detail::QuantityAccessor<typename Domain::AngularState>;
    };

}  // namespace quant::geometry
