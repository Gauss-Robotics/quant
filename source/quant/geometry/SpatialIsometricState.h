#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

#include <string>

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
        using GeometricRepresentationType = Eigen::Isometry3d const&;

        SpatialIsometricState() : _representation(Eigen::Isometry3d::Identity())
        {
            ;
        }

        SpatialIsometricState(LinearStateType const& linear) :
            SpatialIsometricState(linear, AngularStateType::zero())
        {
            ;
        }

        SpatialIsometricState(AngularStateType const& angular) :
            SpatialIsometricState(LinearStateType::zero(), angular)
        {
            ;
        }

        SpatialIsometricState(LinearStateType const& linear, AngularStateType const& angular) :
            _representation{[&linear, &angular]()
                            {
                                using LinearState = detail::StateAccessor<LinearStateType>;
                                using AngularState = detail::StateAccessor<AngularStateType>;

                                Eigen::Isometry3d tf = Eigen::Isometry3d::Identity();
                                tf.translation() = LinearState::representation(linear);
                                tf.linear() =
                                    Eigen::Matrix3d(AngularState::representation(angular));
                                return tf;
                            }()}
        {
            ;
        }

        static StateType
        zero()
        {
            return StateType{Eigen::Isometry3d::Identity()};
        }

        LinearStateType
        linear() const
        {
            using State = detail::StateAccessor<LinearStateType>;
            return State::make(_representation.translation());
        }

        AngularStateType
        angular() const
        {
            using State = detail::StateAccessor<AngularStateType>;
            return State::make(Eigen::Quaterniond(_representation.rotation()));
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

        std::string
        to_string() const
        {
            return linear().to_string() + ", " + angular().to_string();
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
