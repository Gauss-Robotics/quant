#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/forward_declarations.h>

namespace quant::geometry
{

    template <typename StateType>
    class SE3TangentState
    {
    public:
        using LinearStateType = traits::linear_state_in_domain_of<StateType>;
        using AngularStateType = traits::angular_state_in_domain_of<StateType>;
        using LinearDifferenceType = traits::linear_difference_in_domain_of<StateType>;
        using AngularDifferenceType = traits::angular_difference_in_domain_of<StateType>;
        using GeometricRepresentationType = Eigen::Vector<double, 6>;

        SE3TangentState(LinearStateType linear, AngularStateType angular)
        {
            _representation.head(3) =
                detail::StateAccessor<AngularStateType>::representation(angular);
            _representation.tail(3) =
                detail::StateAccessor<LinearStateType>::representation(linear);
        }

        static StateType
        zero()
        {
            return StateType(LinearStateType::zero(), AngularStateType::zero());
        }

        LinearStateType
        linear() const
        {
            return detail::StateAccessor<LinearStateType>::make(_representation.tail(3));
        }

        AngularStateType
        angular() const
        {
            return detail::StateAccessor<AngularStateType>::make(_representation.head(3));
        }

        friend StateType
        operator+(StateType const& lhs, LinearDifferenceType const& op)
        {
            return StateType(lhs.linear() + op, lhs.angular());
        }

        friend StateType
        operator-(StateType const& lhs, LinearStateType const& op)
        {
            return StateType(lhs.linear() - op, lhs.angular());
        }

        friend StateType
        operator+(StateType const& lhs, AngularDifferenceType const& op)
        {
            return StateType(lhs.linear(), lhs.angular() + op);
        }

        friend StateType
        operator-(StateType const& lhs, AngularStateType const& op)
        {
            return StateType(lhs.linear(), lhs.angular() - op);
        }

        std::string
        to_string() const
        {
            return "[" + linear().to_string() + ", " + angular().to_string() + "]";
        }

        bool
        is_approx(StateType const& rhs,
                  double const tolerance = Eigen::NumTraits<double>::dummy_precision()) const
        {
            return _representation.isApprox(rhs._representation, tolerance);
        }

    protected:
        SE3TangentState(GeometricRepresentationType const& eigen) : _representation(eigen)
        {
            ;
        }

        GeometricRepresentationType _representation;

        friend class detail::StateAccessor<StateType>;
    };

}  // namespace quant::geometry
