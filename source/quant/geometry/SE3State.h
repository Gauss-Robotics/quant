#pragma once

#include <quant/geometry/detail/QuantityAccessor.h>

#include <Eigen/Geometry>

#include <string>

namespace quant::geometry
{

    template <typename StateType>
    class SE3State
    {
    public:
        using LinearStateType = traits::linear_state_in_domain_of<StateType>;
        using AngularStateType = traits::angular_state_in_domain_of<StateType>;
        using LinearDifferenceType = traits::linear_difference_in_domain_of<StateType>;
        using AngularDifferenceType = traits::angular_difference_in_domain_of<StateType>;
        using GeometricRepresentationType = Eigen::Isometry3d;

        explicit SE3State() : _representation(Eigen::Isometry3d::Identity())
        {
            ;
        }

        explicit SE3State(LinearStateType const& linear) :
            SE3State(linear, AngularStateType::zero())
        {
            ;
        }

        explicit SE3State(AngularStateType const& angular) :
            SE3State(LinearStateType::zero(), angular)
        {
            ;
        }

        SE3State(LinearStateType const& linear, AngularStateType const& angular) :
            _representation{
                [&linear, &angular]()
                {
                    using LinearState = detail::StateAccessor<LinearStateType>;
                    using AngularState = detail::StateAccessor<AngularStateType>;

                    Eigen::Isometry3d tf = Eigen::Isometry3d::Identity();
                    tf.translation() = LinearState::representation(linear).translation();
                    tf.linear() = Eigen::Matrix3d(AngularState::representation(angular));
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
            return State::make(
                Eigen::Translation3d(_representation.translation()));
        }

        AngularStateType
        angular() const
        {
            using State = detail::StateAccessor<AngularStateType>;
            return State::make(Eigen::Quaterniond(_representation.rotation()));
        }

        // Compare.
        bool
        is_approx(StateType const& rhs,
                  double const tolerance = Eigen::NumTraits<double>::dummy_precision()) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

        std::string
        to_string() const
        {
            return linear().to_string() + ", " + angular().to_string();
        }

        bool
        operator==(StateType const& rhs) const
        {
            return _representation.linear() == rhs._representation.linear() and
                   _representation.translation() == rhs._representation.translation();
        }

        bool
        operator!=(StateType const& rhs) const
        {

            return _representation.linear() != rhs._representation.linear() or
                   _representation.translation() != rhs._representation.translation();
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

        StateType
        inverse() const
        {
            return StateType{_representation.inverse()};
        }

    protected:
        SE3State(Eigen::Isometry3d const& tf) : _representation(tf)
        {
            ;
        }

        SE3State(Eigen::Ref<Eigen::Matrix4f const> const& tf) :
            _representation(tf.cast<double>())
        {
            ;
        }

        SE3State(Eigen::Ref<Eigen::Matrix4d const> const& tf) : _representation(tf)
        {
            ;
        }

        Eigen::Isometry3d _representation;

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry
