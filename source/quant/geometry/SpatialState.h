#pragma once

#include <quant/geometry/Difference.h>
#include <quant/geometry/forward_declarations.h>

namespace quant::geometry
{

    template <typename StateType>
    class SpatialState
    {
    public:
        using LinearStateType = traits::linear_state_in_domain_of<StateType>;
        using AngularStateType = traits::angular_state_in_domain_of<StateType>;
        using LinearDifferenceType = traits::linear_difference_in_domain_of<StateType>;
        using AngularDifferenceType = traits::angular_difference_in_domain_of<StateType>;
        using GeometricRepresentationType = Eigen::Affine3d;

        SpatialState(LinearStateType linear, AngularStateType angular) :
            _linear{linear}, _angular{angular}
        {
            ;
        }

        static StateType
        zero()
        {
            return StateType(LinearStateType::zero(), AngularStateType::zero());
        }

        LinearStateType
        linear() const
        {
            return _linear;
        }

        AngularStateType
        angular() const
        {
            return _angular;
        }

        friend StateType
        operator+(StateType const& lhs, LinearDifferenceType const& op)
        {
            return StateType(lhs._linear + op, lhs._angular);
        }

        friend StateType
        operator-(StateType const& lhs, LinearStateType const& op)
        {
            return StateType(lhs._linear - op, lhs._angular);
        }

        friend StateType
        operator+(StateType const& lhs, AngularDifferenceType const& op)
        {
            return StateType(lhs._linear, lhs._angular + op);
        }

        friend StateType
        operator-(StateType const& lhs, AngularStateType const& op)
        {
            return StateType(lhs._linear, lhs._angular - op);
        }

        std::string to_string() const
        {
            return "[" + _linear.to_string() + ", " + _angular.to_string() + "]";
        }

    protected:
        // GeometricRepresentationType _representation; TODO: do we need this?
        LinearStateType _linear;
        AngularStateType _angular;
    };

}  // namespace quant::geometry
