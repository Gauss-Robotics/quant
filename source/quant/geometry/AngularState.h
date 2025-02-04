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
        using GeometricRepresentationType = Eigen::Vector3d;
        // Construct.

        /**
         * @brief Default constructed quaternion.
         */
        AngularState() : _representation(GeometricRepresentationType::Zero())
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
            return _representation == rhs._representation;
        }

        bool
        operator!=(StateType const& rhs) const
        {
            return _representation != rhs._representation;
        }

        /**
         * @brief Unary minus operator.
         *
         * @return The negated state.
         */
        StateType
        operator-() const
        {
            return StateType{_representation.inverse()};
        }

        bool
        is_approx(StateType const& rhs,
                  double tolerance = constants::floating_point_tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }



    protected:
        // Construct.

        AngularState(AxisAngle const& aa) : _representation{aa.axis.to_eigen().normalized() * aa.angle}
        {
            ;
        }

        AngularState(Eigen::AngleAxisd const& aa) : _representation{aa.axis() * aa.angle()}
        {
            ;
        }

        AngularState(GeometricRepresentationType const& eigen) : _representation{eigen}
        {
            ;
        }

        // Convert.

        AxisAngle
        to_axis_angle() const
        {
            return AxisAngle::from_eigen(
                Eigen::AngleAxisd{_representation.norm(), _representation.normalized()});
        }

        GeometricRepresentationType _representation;

        friend class detail::StateAccessor<StateType>;
    };
}  // namespace quant::geometry
