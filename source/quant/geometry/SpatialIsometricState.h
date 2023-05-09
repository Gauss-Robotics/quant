#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

namespace quant::geometry
{

    template <typename StateType>
    class SpatialIsometricState
    {
    public:
        using LinearStateType = traits::linear_state_in_domain_of<StateType>;
        using AngularStateType = traits::angular_state_in_domain_of<StateType>;
        using LinearDifferenceType = traits::linear_difference_in_domain_of<StateType>;
        using AngularDifferenceType = traits::angular_difference_in_domain_of<StateType>;
        using GeometricType = traits::SpatialStateType;
        using GeometricRepresentationType = Eigen::Isometry3d const&;

        SpatialIsometricState() : _representation(Eigen::Isometry3d::Identity())
        {
            ;
        }

        SpatialIsometricState(LinearStateType linear, AngularStateType angular)
        {
            ;
        }

        static StateType
        zero()
        {
            return StateType{Eigen::Isometry3d::Identity()};
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

        bool
        is_approx(StateType const& rhs, double const tolerance) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

    protected:
        SpatialIsometricState(Eigen::Isometry3d const& tf) : _representation(tf)
        {
            ;
        }

        SpatialIsometricState(Eigen::Ref<const Eigen::Matrix4f> const& tf) :
            _representation(tf.cast<double>())
        {
            ;
        }

        SpatialIsometricState(Eigen::Ref<const Eigen::Matrix4d> const& tf) : _representation(tf)
        {
            ;
        }

        Eigen::Isometry3d _representation;

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry
